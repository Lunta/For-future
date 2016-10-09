from SpriteImage import*


class Meteor:

    def __init__(self, x, y, speed, type_m, stage=0, random_vector=False):
        self.m_TypeList = \
            [
                'Small',
                'Big',
                'Huge',
                'Boss'
            ]
        self._m_BossImagePath_List = \
            [
                'Resource\Graphics\Object\Boss_Mercury1.png',
                'Resource\Graphics\Object\Boss_Venus2.png',
                'Resource\Graphics\Object\Boss_Mars3.png',
                'Resource\Graphics\Object\Boss_Jupiter4.png',
                'Resource\Graphics\Object\Boss_Saturn5.png',
                'Resource\Graphics\Object\Boss_Uranus6.png',
                'Resource\Graphics\Object\Boss_Neptune7.png'
            ]
        self._m_ImagePath_List = \
            [
                'Resource\Graphics\Object\Stone_Small.png',
                'Resource\Graphics\Object\Stone_Big.png',
                'Resource\Graphics\Object\Stone_Huge.png',
            ]
        self._m_EffectImage_path_List = \
            [
                'Resource\Graphics\Sprite\Effect\Effect_Small.png',
                'Resource\Graphics\Sprite\Effect\Effect_Big.png',
                'Resource\Graphics\Sprite\Effect\Effect_Huge.png',
                'Resource\Graphics\Sprite\Effect\Effect_Boss.png'
            ]
        self._m_x = x
        self._m_y = y
        self._m_Speed = speed
        self._m_Type = type_m
        if random_vector:
            self._m_DVector = Vector2D(0, 0)
        else:
            self._m_DVector = Vector2D(-1, 0)

        if self._m_Type is 'Boss':
            self._m_Image = load_image(self._m_BossImagePath_List[stage])
            self._m_EffectImage = SpriteImage(self._m_EffectImage_path_List[self.m_TypeList.index(self._m_Type)], 'Boss_Effect', 4)
        else:
            self._m_Image = load_image(self._m_ImagePath_List[self.m_TypeList.index(self._m_Type)])
            self._m_EffectImage = SpriteImage(self._m_EffectImage_path_List[self.m_TypeList.index(self._m_Type)], 'Boss_Effect', 4)
        self._m_bEffect = True
        self._m_Radian = 0.0

    def update(self, TimeElapsed):
        self._m_EffectImage.update()
        self._m_x += self._m_DVector.x * self._m_Speed
        if self._m_Radian >= math.pi * 2:
            self._m_Radian = 0
        elif self._m_Type is not 'Boss':
            self._m_Radian += TimeElapsed
        elif self._m_Type is 'Boss':
            self._m_Radian += TimeElapsed * 10

    def draw(self):
        self._m_Image.rotate_draw(self._m_Radian, self._m_x, self._m_y)
        if self._m_bEffect or self._m_Type is 'Boss':
            self._m_EffectImage.draw(self._m_x, self._m_y)

    def release(self):
        del self._m_Image
        del self._m_EffectImage
        del self.m_TypeList
        del self._m_ImagePath_List
        del self._m_BossImagePath_List
        del self._m_EffectImage_path_List
        del self._m_DVector
