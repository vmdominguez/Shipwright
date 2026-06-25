#include <ship/window/Window.h>
#include <ship/window/gui/Gui.h>

class FakeWindow : public Ship::Window {
  public:
    FakeWindow(std::shared_ptr<Ship::Gui> gui) : Window::Window(gui) {
    }

    void Init() {}
    void Close() {}
    void RunGuiOnly() {}
    void StartFrame() {}
    void EndFrame() {}
    bool IsFrameReady() {
      return false;
    }
    void HandleEvents() {}
    void SetCursorVisibility(bool visible) {}
    uint32_t GetWidth() {
      return 0;
    }
    uint32_t GetHeight() {
      return 0;
    }
    int32_t GetPosX() {
      return 0;
    }
    int32_t GetPosY() {
      return 0;
    }
    float GetAspectRatio() {
      return 0;
    }
    void SetMousePos(Ship::Coords pos) {}
    Ship::Coords GetMousePos() {
      return {0, 0};
    }
    Ship::Coords GetMouseDelta() {
      return {0, 0};
    }
    Ship::CoordsF GetMouseWheel() {
      return {0, 0};
    }
    bool GetMouseState(Ship::MouseBtn btn) {
      return false;
    }
    void SetMouseCapture(bool capture) {}
    bool IsMouseCaptured() {
      return false;
    }
    uint32_t GetCurrentRefreshRate() {
      return 0;
    }
    bool SupportsWindowedFullscreen() {
      return false;
    }
    bool CanDisableVerticalSync() {
      return false;
    }
    void SetResolutionMultiplier(float multiplier) {}
    void SetMsaaLevel(uint32_t value) {}
    void SetFullscreen(bool isFullscreen) {}
    bool IsFullscreen() {
      return false;
    }
    bool IsRunning() {
      return false;
    }
    uintptr_t GetGfxFrameBuffer() {
      return 0;
    }
    const char* GetKeyName(int32_t scancode) {
      return "FakeWindow";
    }

    void SetCurrentDimensions(uint32_t width, uint32_t height) {}
    void SetCurrentDimensions(uint32_t width, uint32_t height, int32_t posX, int32_t posY) {}
    void SetCurrentDimensions(bool isFullscreen, uint32_t width, uint32_t height) {}
    void SetCurrentDimensions(bool isFullscreen, uint32_t width, uint32_t height, int32_t posX, int32_t posY) {}
    Ship::WindowRect GetPrimaryMonitorRect() {
      return {0, 0, 0, 0};
    }
};
