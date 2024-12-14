#include "Setting.h"
Setting::Setting(int width, int height, int fpsLimit):windowWidth(width),windowHeight(height),fpsLimit(fpsLimit){}
int Setting::getFpsLimit() {
    return this->fpsLimit;
}
int Setting::getWindowWidth() {
    return this->windowWidth;
}
int Setting::getWindowHeight() {
    return this->windowHeight;
}
void Setting::setFpsLimit(int fpsLimit) {
    this->fpsLimit = fpsLimit;
}
void Setting::setWindowWidth(int width) {
    this->windowWidth = width;
}
void Setting::setWindowHeight(int height) {
    this->windowHeight = height;
}