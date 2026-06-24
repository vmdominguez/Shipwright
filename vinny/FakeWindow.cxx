#include "FakeWindow.h"

FakeWindow::FakeWindow(std::shared_ptr<Ship::Gui> gui) : Window::Window(gui) {
}

void FakeWindow::Init() {}
void FakeWindow::Close() {}
void FakeWindow::RunGuiOnly() {}
void FakeWindow::StartFrame() {}
void FakeWindow::EndFrame() {}
bool FakeWindow::IsFrameReady() {
  return false;
}
void FakeWindow::HandleEvents() {}
void FakeWindow::SetCursorVisibility(bool visible) {}
uint32_t FakeWindow::GetWidth() {
  return 0;
}
uint32_t FakeWindow::GetHeight() {
  return 0;
}
int32_t FakeWindow::GetPosX() {
  return 0;
}
int32_t FakeWindow::GetPosY() {
  return 0;
}
float FakeWindow::GetAspectRatio() {
  return 0;
}
void FakeWindow::SetMousePos(Ship::Coords pos) {}
Ship::Coords FakeWindow::GetMousePos() {
  return {0, 0};
}
Ship::Coords FakeWindow::GetMouseDelta() {
  return {0, 0};
}
Ship::CoordsF FakeWindow::GetMouseWheel() {
  return {0, 0};
}
bool FakeWindow::GetMouseState(Ship::MouseBtn btn) {
  return false;
}
void FakeWindow::SetMouseCapture(bool capture) {}
bool FakeWindow::IsMouseCaptured() {
  return false;
}
uint32_t FakeWindow::GetCurrentRefreshRate() {
  return 0;
}
bool FakeWindow::SupportsWindowedFullscreen() {
  return false;
}
bool FakeWindow::CanDisableVerticalSync() {
  return false;
}
void FakeWindow::SetResolutionMultiplier(float multiplier) {}
void FakeWindow::SetMsaaLevel(uint32_t value) {}
void FakeWindow::SetFullscreen(bool isFullscreen) {}
bool FakeWindow::IsFullscreen() {
  return false;
}
bool FakeWindow::IsRunning() {
  return false;
}
uintptr_t FakeWindow::GetGfxFrameBuffer() {
  return 0;
}
const char* FakeWindow::GetKeyName(int32_t scancode) {
  return "FakeWindow";
}

void FakeWindow::SetCurrentDimensions(uint32_t width, uint32_t height) {}
void FakeWindow::SetCurrentDimensions(uint32_t width, uint32_t height, int32_t posX, int32_t posY) {}
void FakeWindow::SetCurrentDimensions(bool isFullscreen, uint32_t width, uint32_t height) {}
void FakeWindow::SetCurrentDimensions(bool isFullscreen, uint32_t width, uint32_t height, int32_t posX, int32_t posY) {}
Ship::WindowRect FakeWindow::GetPrimaryMonitorRect() {
  return {0, 0, 0, 0};
}
