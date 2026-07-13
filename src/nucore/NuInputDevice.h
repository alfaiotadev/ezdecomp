#pragma once
enum NUPADMOTIONVALUE {
    NU_MOTION_TILT_X = 0,
    NU_MOTION_TILT_Y = 1,
    NU_MOTION_TILT_Z = 2,

    // todo 3-5: Likely Gyroscope angular velocity or reserved

    NU_MOTION_ACCEL_X = 6,
    NU_MOTION_ACCEL_Y = 7,
    NU_MOTION_ACCEL_Z = 8,

    NU_MOTION_MAX = 9
};
enum NUPADANALOGVALUE {
    NU_ANALOG_FACE_BUTTON_1 = 0,
    NU_ANALOG_FACE_BUTTON_2 = 1,
    NU_ANALOG_FACE_BUTTON_3 = 2,
    NU_ANALOG_FACE_BUTTON_4 = 3,

    NU_ANALOG_L1 = 4,
    NU_ANALOG_R1 = 5,
    NU_ANALOG_L2 = 6,
    NU_ANALOG_R2 = 7,

    NU_ANALOG_LEFT_STICK_X = 8,
    NU_ANALOG_LEFT_STICK_Y = 9,

    NU_ANALOG_RIGHT_STICK_X = 10,
    NU_ANALOG_RIGHT_STICK_Y = 11,

    NU_ANALOG_MAX = 12
};

struct NuInputTouchData {
    unsigned int Count;
    struct TouchPoint {
        int x;
        int y;
        int id;
        int flags;
    } Points[10];
};

struct NuInputMouseData {
    unsigned int Flags;
    unsigned long long Position;
};

struct NuInputDeviceTranslator {};
class NuInputDevice {
public:
    NuInputDevice(unsigned int port);
    ~NuInputDevice();

    int GetCaps() const;
    void Update(float deltaTime, bool someFlag);
    void KillRumble();
    int GetType() const;
    void SetDisconnected();
    void Clear();
    void DeadZone(NUPADANALOGVALUE analogValue, float deadZone);
    void AddTranslator(NuInputDeviceTranslator* translator);
    void ConvertToEmulatedTouchFromMouse();
    void ProcessTouchData();
    unsigned int GetPort() const;
    unsigned int GetIdentifier_CAFE_SPECIFIC() const;
    int GetLastValidType() const;
    int GetAttachmentType() const;
    bool SupportsCaps(unsigned int cap) const;
    bool IsConnected() const;
    bool IsIntercepted() const;
    bool IsButtonPressed(unsigned int button) const;
    unsigned int GetButtons() const;
    float GetAnalogValue(NUPADANALOGVALUE index) const;
    float GetMotionValue(NUPADMOTIONVALUE index) const;
    const NuInputTouchData* GetTouchData() const;
    const NuInputMouseData* GetMouseData() const;
    void SetMotors(float lowFreq, float highFreq);
    void EnableDPD();
    void DisableDPD();
    bool HasHeadphonesConnected() const;
    float GetVolume() const;
    unsigned int GetSortKey() const;

private:
    unsigned int m_Port;
    int m_CafeSpecificId;
    int m_Type;
    int m_LastValidType;
    unsigned int m_AttachmentType;
    unsigned int m_Caps;
    bool m_IsConnected;
    bool m_IsIntercepted;
    unsigned int m_Buttons;
    float m_AnalogValues[NU_ANALOG_MAX];
    float m_MotionValues[20];
    NuInputTouchData m_PrevTouchData;
    NuInputTouchData m_TouchData;
    NuInputMouseData m_MouseData;
    float m_LowFreqMotor;
    float m_HighFreqMotor;
    bool m_RumbleKilled;
    float m_RumbleIdleTimer;
    float m_RumbleDuration;
    bool m_HasHeadphones;
    float m_Volume;
    NuInputDeviceTranslator* m_Translators[2];
    int m_TranslatorCount;
    int m_SortKey;
};
