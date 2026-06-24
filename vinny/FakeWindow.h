#include <ship/window/Window.h>
#include <ship/window/gui/Gui.h>

/**
 * Fake Ship::Window implementation in order to satisfy constraints from using Ship::Context.
 */
class FakeWindow : public Ship::Window {
  public:
    FakeWindow(std::shared_ptr<Ship::Gui> gui);
    void Init() override;
    void Close() override;
    void RunGuiOnly() override;
    void StartFrame() override;
    void EndFrame() override;
    bool IsFrameReady() override;
    void HandleEvents() override;
    void SetCursorVisibility(bool visible) override;
    uint32_t GetWidth() override;
    uint32_t GetHeight() override;
    int32_t GetPosX() override;
    int32_t GetPosY() override;
    float GetAspectRatio() override;
    void SetMousePos(Ship::Coords pos) override;
    Ship::Coords GetMousePos() override;
    Ship::Coords GetMouseDelta() override;
    Ship::CoordsF GetMouseWheel() override;
    bool GetMouseState(Ship::MouseBtn btn) override;
    void SetMouseCapture(bool capture) override;
    bool IsMouseCaptured() override;
    uint32_t GetCurrentRefreshRate() override;
    bool SupportsWindowedFullscreen() override;
    bool CanDisableVerticalSync() override;
    void SetResolutionMultiplier(float multiplier) override;
    void SetMsaaLevel(uint32_t value) override;
    void SetFullscreen(bool isFullscreen) override;
    bool IsFullscreen() override;
    bool IsRunning() override;
    uintptr_t GetGfxFrameBuffer() override;
    const char* GetKeyName(int32_t scancode) override;

    void SetCurrentDimensions(uint32_t width, uint32_t height) override;
    void SetCurrentDimensions(uint32_t width, uint32_t height, int32_t posX, int32_t posY) override;
    void SetCurrentDimensions(bool isFullscreen, uint32_t width, uint32_t height) override;
    void SetCurrentDimensions(bool isFullscreen, uint32_t width, uint32_t height, int32_t posX, int32_t posY) override;
    Ship::WindowRect GetPrimaryMonitorRect() override;
};
