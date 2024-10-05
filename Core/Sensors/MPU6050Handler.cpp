#define MPU6050_INCLUDE_DMP_MOTIONAPPS20

#define OUTPUT_READABLE_YAWPITCHROLL
#define OUTPUT_READABLE_REALACCEL
#define OUTPUT_READABLE_WORLDACCEL
#define OUTPUT_READABLE_CUSTOM

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "MPU6050I2Cdev/MPU6050_6Axis_MotionApps_V6_12.h"
#include "MPU6050I2Cdev/mpu6050_calibration.cpp"

MPU6050 mpu;

// This Old code, maybe we can need in future
/*struct AccellGyroStruct
{
    int16_t acceleration[3];
    int16_t gyro[3];
    int16_t temp;
};
// By default these devices  are on bus address 0x68
static int addr = 0x68;

#ifdef i2c_default
static void mpu6050_reset()
{
    // Two byte reset. First byte register, second byte data
    // There are a load more options to set up the device in different ways that could be added here
    uint8_t buf[] = {0x6B, 0x00};
    i2c_write_blocking(i2c_default, addr, buf, 2, false);
}

static void mpu6050_read_raw(int16_t accel[3], int16_t gyro[3], int16_t *temp)
{
    // For this particular device, we send the device the register we want to read
    // first, then subsequently read from the device. The register is auto incrementing
    // so we don't need to keep sending the register we want, just the first.

    uint8_t buffer[6];

    // Start reading acceleration registers from register 0x3B for 6 bytes
    uint8_t val = 0x3B;
    i2c_write_blocking(i2c_default, addr, &val, 1, true); // true to keep master control of bus
    i2c_read_blocking(i2c_default, addr, buffer, 6, false);

    for (int i = 0; i < 3; i++)
    {
        accel[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }

    // Now gyro data from reg 0x43 for 6 bytes
    // The register is auto incrementing on each read
    val = 0x43;
    i2c_write_blocking(i2c_default, addr, &val, 1, true);
    i2c_read_blocking(i2c_default, addr, buffer, 6, false); // False - finished with bus

    for (int i = 0; i < 3; i++)
    {
        gyro[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }

    // Now temperature from reg 0x41 for 2 bytes
    // The register is auto incrementing on each read
    val = 0x41;
    i2c_write_blocking(i2c_default, addr, &val, 1, true);
    i2c_read_blocking(i2c_default, addr, buffer, 2, false); // False - finished with bus

    *temp = buffer[0] << 8 | buffer[1];
}
#endif

int Run_MPU5060(AccellGyroStruct *outParam)
{

#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
#warning i2c/mpu6050_i2c example requires a board with I2C pins
    puts("Default I2C pins were not defined");
#else

    printf("Hello, MPU6050! Reading raw data from registers...\n");
    mpu6050_read_raw(outParam->acceleration, outParam->gyro, &outParam->temp);
    outParam->temp = ((outParam->temp / 340.0) + 36.53);
    // These are the raw numbers from the chip, so will need tweaking to be really useful.
    // See the datasheet for more information
    printf("Acc. X = %d, Y = %d, Z = %d\n", outParam->acceleration[0], outParam->acceleration[1], outParam->acceleration[2]);
    printf("Gyro. X = %d, Y = %d, Z = %d\n", outParam->gyro[0], outParam->gyro[1], outParam->gyro[2]);
    // Temperature is simple so use the datasheet calculation to get deg C.
    // Note this is chip temperature.
    printf("Temp. = %f\n", (outParam->temp / 340.0) + 36.53);

#endif
    return 0;
}
*/

bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

Quaternion q;        // [w, x, y, z]         quaternion container
VectorInt16 aa;      // [x, y, z]            accel sensor measurements
VectorInt16 gy;      // [x, y, z]            gyro sensor measurements
VectorInt16 aaReal;  // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld; // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity; // [x, y, z]            gravity vector
float euler[3];      // [psi, theta, phi]    Euler angle container
float ypr[3];        // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
float yaw, pitch, roll;

volatile bool mpuInterrupt = false; // indicates whether MPU interrupt pin has gone high
void MPU6050_dmpDataReady()
{
    mpuInterrupt = true;
}

void MPU6050_Init()
{
    mpu.initialize();
    devStatus = mpu.dmpInitialize();

    mpu.setXGyroOffset(53);
    mpu.setYGyroOffset(-62);
    mpu.setZGyroOffset(15);
    mpu.setXAccelOffset(-4789);
    mpu.setYAccelOffset(-1211);
    mpu.setZAccelOffset(1132);

    if (devStatus == 0)
    {
        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        mpu.PrintActiveOffsets();

        mpu.setDMPEnabled(true); // turn on the DMP, now that it's ready
        mpuIntStatus = mpu.getIntStatus();
        dmpReady = true;                         // set our DMP Ready flag so the main loop() function knows it's okay to use it
        packetSize = mpu.dmpGetFIFOPacketSize(); // get expected DMP packet size for later comparison
    }
    else
    { // ERROR!        1 = initial memory load failed         2 = DMP configuration updates failed        (if it's going to break, usually the code will be 1)
        printf("DMP Initialization failed (code %d)", devStatus);
        sleep_ms(2000);
    }
    yaw = 0.0;
    pitch = 0.0;
    roll = 0.0;
}

void MPU6050_YawPitchRoll(float *CurrentYaw, float *CurrentPitch, float *CurrentRoll, float *SensorTemp)
{
    if (!dmpReady)
        ; // if programming failed, don't try to do anything
    mpuInterrupt = true;
    fifoCount = mpu.getFIFOCount();                 // get current FIFO count
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) // check for overflow (this should never happen unless our code is too inefficient)
    {
        mpu.resetFIFO(); // reset so we can continue cleanly
        printf("FIFO overflow!");
    }
    else if (mpuIntStatus & 0x01) // otherwise, check for DMP data ready interrupt (this should happen frequently)
    {
        while (fifoCount < packetSize)
            fifoCount = mpu.getFIFOCount();       // wait for correct available data length, should be a VERY short wait
        mpu.getFIFOBytes(fifoBuffer, packetSize); // read a packet from FIFO
        fifoCount -= packetSize;                  // track FIFO count here in case there is > 1 packet available
#ifdef OUTPUT_READABLE_YAWPITCHROLL               // display Euler angles in degrees
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
        *SensorTemp = mpu.getTemperature() / 100;
        yaw = ypr[0] * 180 / PI;
        pitch = ypr[1] * 180 / PI;
        roll = ypr[2] * 180 / PI;
        *CurrentYaw = yaw;
        *CurrentPitch = pitch;
        *CurrentRoll = roll;
        // printf("ypr: %f,\t %f,\t  %f,\t %f\n", yaw, pitch, roll, SensorTemp);
#endif
#ifdef OUTPUT_READABLE_REALACCEL
        // display real acceleration, adjusted to remove gravity
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetAccel(&aa, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
        printf("areal: %d,\t %d,\t %d\n", aaReal.x, aaReal.y, aaReal.z);
#endif
#ifdef OUTPUT_READABLE_WORLDACCEL
        // display initial world-frame acceleration, adjusted to remove gravity
        // and rotated based on known orientation from quaternion
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetAccel(&aa, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
        mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
        printf("aworld: %d,\t %d,\t %d\n", aaWorld.x, aaWorld.y, aaWorld.z);
#endif
#ifdef OUTPUT_READABLE_CUSTOM
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        printf("W: %f\t X: %f\t Y: %f\t Z: %f\n", q.w, q.x, q.y, q.z);
#endif
    }
}

// sometimes need read from know in what direction we move
void MPU6050_AccellXYZ() {}

void MPU6050_Calibrating()
{

#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
#warning i2c/mpu6050_i2c example requires a board with I2C pins
    puts("Default I2C pins were not defined");
#else

    // Calibrate();

#endif
}
