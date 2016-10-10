from pico2d import*
from Utility import*


class SpriteImage:
    def __init__(self, path, sprite_name=None, w=1, h=1):
        if sprite_name is not None:
            self._m_name = sprite_name

        self._m_SpriteImage = load_image(path)

        self._m_FrameXNum = w
        self._m_FrameYNum = h

        self._m_nFrameWidthSize = int(self._m_SpriteImage.w / self._m_FrameXNum) + 1
        self._m_nFrameHeightSize = int(self._m_SpriteImage.h / self._m_FrameYNum)

        self._m_ptCurrentAnimationState = POINT()
        self._m_ptCurrentAnimationState.x = 0
        self._m_ptCurrentAnimationState.y = 0

    def update(self):
        self._m_ptCurrentAnimationState.x += 1

        if self._m_ptCurrentAnimationState.x >= self._m_FrameXNum:
            self._m_ptCurrentAnimationState.x = 0
            self._m_ptCurrentAnimationState.y += 1

        if self._m_ptCurrentAnimationState.y >= self._m_FrameYNum:
            self._m_ptCurrentAnimationState.y = 0

    def draw(self, x, y):
        self._m_SpriteImage.clip_draw(
            self._m_nFrameWidthSize * self._m_ptCurrentAnimationState.x,
            self._m_nFrameHeightSize * self._m_ptCurrentAnimationState.y,
            self._m_nFrameWidthSize,
            self._m_nFrameHeightSize,
            x, y
        )

    def set_currentframe(self, x, y=0):
        self._m_ptCurrentAnimationState.x = x
        self._m_ptCurrentAnimationState.y = y

    def get_currentframe_x(self):
        return self._m_ptCurrentAnimationState.x

    def get_frame_width(self):
        return self._m_nFrameWidthSize

    def get_frame_height(self):
        return self._m_nFrameHeightSize

    def get_name(self):
        return self._m_name

    def release(self):
        del self._m_SpriteImage

