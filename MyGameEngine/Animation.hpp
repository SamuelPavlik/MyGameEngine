#ifndef Animation_hpp
#define Animation_hpp

#include <vector>

struct FrameData {
    int id;
    int x;
    int y;
    int width;
    int height;
    float displayTimeSeconds;
};

class Animation {
public:
    Animation();

    void AddFrame(int textureID, int x, int y,
        int width, int height, float frameTime);

    const FrameData* GetCurrentFrame() const;

    bool UpdateFrame(float deltaTime);

    void Reset();

private:
    void IncrementFrame();

    // Stores all frames for our animation.
    std::vector<FrameData> frames;

    // Current frame.
    int currentFrameIndex;

    // We use this to decide when to transition to the next frame.
    float currentFrameTime;
};

#endif /* Animation_hpp */