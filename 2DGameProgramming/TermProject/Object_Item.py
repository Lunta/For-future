from SpriteImage import *


class Item:
    _m_ItemType_List = \
        [
            'PowerUp'
        ]
    _m_ItemPath_List = \
        [
            'Resource\Graphics\Object\Stone_Small.png'
        ]
    _m_type = None
    _m_Image = None
    _m_x = 0
    _m_y = 0

    def __init__(self, itype, x, y):
        self._m_Image = SpriteImage(self._m_ItemPath_List[self._m_ItemType_List.index(itype)])
        self._m_x = x
        self._m_y = y

    def update(self):
        self._m_Image.update()

    def draw(self):
        self._m_Image.draw(self._m_x, self._m_y)

    def release(self):
        self._m_Image.release()
        del self._m_ItemPath_List
        del self._m_ItemType_List

