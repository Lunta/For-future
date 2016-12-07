from SpriteImage import *


class Item:
    def __init__(self, x, y, client_width, client_height):
        self.CLIENT_WIDTH = client_width
        self.CLIENT_HEIGHT = client_height
        self._m_Image = SpriteImage('Resource\Graphics\Sprite\Effect\Item.png', 'Item', 4)
        self._m_x = x
        self._m_y = y
        self.CheckBox = \
            Rect(self._m_x - self._m_Image.get_frame_width() / 2, self._m_y - self._m_Image.get_frame_height() / 2,
                 self._m_x + self._m_Image.get_frame_width() / 2, self._m_y + self._m_Image.get_frame_height() / 2)
        vx, vy = random.randint(-10, 10), random.randint(-10, 10)
        while vx is 0 and vy is 0:
            vx, vy = random.randint(-10, 10), random.randint(-10, 10)
        self._m_DVector = Vector2D(vx, vy)
        self._m_DVector.normalize()
        self._m_Speed = random.randint(100, 200)

        self._m_UseAble = True

    def update(self, TimeElapsed):
        self._m_Image.update()
        self.move(TimeElapsed)
        self.bounce()
        self.CheckBox.set_parameter(
            self._m_x - self._m_Image.get_frame_width() / 2, self._m_y - self._m_Image.get_frame_height() / 2,
            self._m_x + self._m_Image.get_frame_width() / 2, self._m_y + self._m_Image.get_frame_height() / 2)

    def draw(self, purse_y):
        self._m_Image.draw(self._m_x, self._m_y + purse_y)
        # self.CheckBox.draw(purse_y)

    def move(self, TimeElapsed):
        self._m_x += self._m_DVector.x * self._m_Speed * TimeElapsed
        self._m_y += self._m_DVector.y * self._m_Speed * TimeElapsed

    def use(self):
        self._m_UseAble = False
        return True

    def is_used(self):
        return not self._m_UseAble

    def bounce(self):
        if self._m_x > self.CLIENT_WIDTH or self._m_x < 0:
            self._m_DVector.x = -self._m_DVector.x
            if self._m_DVector.x > self.CLIENT_WIDTH:
                self._m_x -= 10
        if self._m_y > self.CLIENT_HEIGHT or self._m_y < 0:
            self._m_DVector.y = -self._m_DVector.y

    def release(self):
        self._m_Image.release()
        del self._m_Image

