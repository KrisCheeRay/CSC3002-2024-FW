#ifndef SETTING_H
#define SETTING_H
class Setting
{
	private:
		int fpsLimit;
		int windowWidth;
		int windowHeight;
	public:
		Setting(int width=1600, int height=1000, int fpsLimit=60);
		virtual int getFpsLimit();
        virtual int getWindowWidth();
        virtual int getWindowHeight();
		virtual void setFpsLimit(int fpsLimit);
        virtual void setWindowWidth(int width);
        virtual void setWindowHeight(int height);
};


#endif // 


