from SpriteAnimation import*


class Player:
    _m_SpritePath_List = \
        [

        ]

    # ex) Idle, Attack
    _m_SpriteState_List = \
        [

        ]

    def __init__(self, x, y):
        self._m_Animation = SpriteAnimation()
        self._m_x = x
        self._m_y = y

    def update(self, TimeElapsed):
        self._m_Animation.update()

    def draw(self):
        pass

    def release(self):
        del self._m_Animation
        del self._m_SpritePath_List

