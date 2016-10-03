from SpriteImage import*


class Meteor:
    m_TypeList = \
        [
            'Small',
            'Big',
            'Huge',
            'Boss'
        ]
    _m_Image_path_List = \
        [
            'Resource\Graphics\Object\Stone_Small.png',
            'Resource\Graphics\Object\Stone_Big.png',
            'Resource\Graphics\Object\Stone_Huge.png',
        ]
    _m_EffectImage_path_List =\
        [
            'Resource\Graphics\Sprite\Effect_Small.png',
            'Resource\Graphics\Sprite\Effect_Big.png',
            'Resource\Graphics\Sprite\Effect_Huge.png',
            'Resource\Graphics\Sprite\Effect_Boss.png'
        ]
    _m_Image = None
    _m_EffectImage = None
    _m_Type = None
    _m_x = 0
    _m_y = 0
    _m_DVector = Vector2D(-1, 0)
    _m_Speed = 0.0
    _m_Radian = 0.0
    _m_bEffect = True

    def __init__(self, x, y, type_m, random_vector=False):
        self._m_x = x
        self._m_y = y
        if random_vector:
            self._m_DVector = Vector2D(0, 0)
        if type_m == 'Boss':
            self._m_EffectImage = SpriteImage(self._m_EffectImage_path_List[self.m_TypeList.index(type_m)], 4)
        else:
            self._m_Image = load_image(self._m_Image_path_List[self.m_TypeList.index(type_m)])
            self._m_EffectImage = SpriteImage(self._m_EffectImage_path_List[self.m_TypeList.index(type_m)], 4)

    def update(self, TimeElapsed):
        self._m_EffectImage.update()
        if self._m_Radian >= math.pi * 2:
            self._m_Radian = 0
        else:
            self._m_Radian += TimeElapsed

    def draw(self):
        self._m_Image.rotate_draw(self._m_Radian, self._m_x, self._m_y)
        if self._m_bEffect:
            self._m_EffectImage.draw(self._m_x, self._m_y)

    def release(self):
        del self._m_Image
        del self._m_EffectImage
        del self.m_TypeList
        del self._m_Image_path_List
        del self._m_EffectImage_path_List
        del self._m_DVector
