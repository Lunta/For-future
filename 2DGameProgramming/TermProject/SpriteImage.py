from pico2d import*
from Utility import*


class SpriteImage:
    def __init__(self, path=None, w=1, h=1):
        if path is not None:
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

    def release(self):
        del self._m_SpriteImage

