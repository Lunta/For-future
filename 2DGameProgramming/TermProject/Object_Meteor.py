from SpriteImage import*


class Meteor:
    def __init__(self, x, y, speed, type_m, client_width, client_height, stage=0, random_vector=False):
        self._m_Type = type_m
        self._m_Stage = stage
        self._m_client_width = client_width
        self._m_client_height = client_height

        # Set List
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
        self._m_MeteorHP_List = \
            [
                10,  # Small
                30,  # Big
                50,  # Huge
                100,  # Boss stage0
                100,  # Boss stage1
                100,  # Boss stage2
                100,  # Boss stage3
                100,  # Boss stage4
                100,  # Boss stage5
                100  # Boss stage6
            ]
        # Set Image
        if self._m_Type is 'Boss':
            self._m_Image = load_image(self._m_BossImagePath_List[self._m_Stage])
            self._m_EffectImage = \
                SpriteImage(self._m_EffectImage_path_List[self.m_TypeList.index(self._m_Type)], self._m_Type + '_Effect', 4)
        else:
            self._m_Stage = 0
            self._m_Image = load_image(self._m_ImagePath_List[self.m_TypeList.index(self._m_Type)])
            self._m_EffectImage = \
                SpriteImage(self._m_EffectImage_path_List[self.m_TypeList.index(self._m_Type)], self._m_Type + '_Effect', 4)

        # Set State
        self._m_x = x
        self._m_y = y
        self._m_PrevHP = self._m_MeteorHP_List[self.m_TypeList.index(self._m_Type) + self._m_Stage]
        self._m_HP = self._m_PrevHP
        self._m_Speed = speed
        if random_vector:
            self._m_DVector = Vector2D(0, 0)
        else:
            self._m_DVector = Vector2D(-self._m_x, self._m_client_height / 2 - self._m_y)
        self._m_DVector.normalize()
        self.CheckBox = \
            Rect(self._m_x - self._m_Image.w / 2, self._m_y - self._m_Image.h / 2,
                 self._m_x + self._m_Image.w / 2, self._m_y + self._m_Image.h / 2)
        self._m_Radian = 0.0
        self._m_HitTimer = 0.0
        self.HIT_TIME = 0.2

        # Set Boolean
        self._m_bEffect = True
        self._m_Hit = False

    def update(self, TimeElapsed):
        if self.check_hit():
            self._m_HitTimer += TimeElapsed
            self.CheckBox.set_parameter()
            if self._m_HitTimer > self.HIT_TIME:
                self._m_HitTimer = 0.0
                self._m_Hit = False
            return None
        else:
            self.CheckBox = \
                Rect(self._m_x - self._m_Image.w / 2, self._m_y - self._m_Image.h / 2,
                     self._m_x + self._m_Image.w / 2, self._m_y + self._m_Image.h / 2)
        self._m_EffectImage.update()
        self._m_x += self._m_DVector.x * self._m_Speed * TimeElapsed
        self._m_y += self._m_DVector.y * self._m_Speed * TimeElapsed

        if self._m_Radian >= math.pi * 2:
            self._m_Radian = 0
        elif self._m_Type is not 'Boss':
            self._m_Radian += TimeElapsed
        elif self._m_Type is 'Boss':
            self._m_Radian += TimeElapsed * 10

    def draw(self, purse_y):
        self._m_Image.rotate_draw(self._m_Radian, self._m_x, self._m_y + purse_y)
        if self._m_bEffect or self._m_Type is 'Boss':
            self._m_EffectImage.draw(self._m_x, self._m_y + purse_y)
        self.CheckBox.draw(purse_y)

    def check_hit(self):
        if self._m_HP is not self._m_PrevHP:
            self._m_PrevHP = self._m_HP
            self._m_Hit = True
            # TODO: 피격 사운드 출력
        return self._m_Hit

    def hit(self, atk):
        if self._m_HP is self._m_PrevHP:
            self._m_HP -= atk

    def release(self):
        del self._m_Image
        del self._m_EffectImage
        del self.m_TypeList
        del self._m_ImagePath_List
        del self._m_BossImagePath_List
        del self._m_EffectImage_path_List
        del self._m_DVector
