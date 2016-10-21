from SpriteImage import*


class Meteor:
    # Set List
    TypeList = \
        [
            'Small',
            'Big',
            'Huge',
            'Boss'
        ]
    MeteorHP_List = \
        [
            5,  # Small
            10,  # Big
            15,  # Huge
            100,  # Boss stage0
            100,  # Boss stage1
            100,  # Boss stage2
            100,  # Boss stage3
            100,  # Boss stage4
            100,  # Boss stage5
            100  # Boss stage6
        ]

    # 경직시간
    HIT_TIME = 0.1
    BORN_TIME = 0.5

    def __init__(self, image_manager, x, y, speed, type_m, client_width, client_height, random_vector=False, stage=0):
        self.ImageManager = image_manager
        self.CLIENT_WIDTH = client_width
        self.CLIENT_HEIGHT = client_height
        self._m_Type = type_m
        self._m_Stage = stage

        # Set Image
        if self._m_Type is 'Small':
            self._m_Image = image_manager.Image_Meteor_Small
            self._m_EffectImage = image_manager.SpriteImage_MeteorEffect_Small
        elif self._m_Type is 'Big':
            self._m_Image = image_manager.Image_Meteor_Big
            self._m_EffectImage = image_manager.SpriteImage_MeteorEffect_Big
        elif self._m_Type is 'Huge':
            self._m_Image = image_manager.Image_Meteor_Huge
            self._m_EffectImage = image_manager.SpriteImage_MeteorEffect_Huge
        elif self._m_Type is 'Boss':
            self._m_Image = image_manager.Image_Meteor_Boss_List[stage]
            self._m_EffectImage = image_manager.SpriteImage_MeteorEffect_Boss

        # Set State
        self._m_x = x
        self._m_y = y
        self._m_PrevHP = self.MeteorHP_List[self.TypeList.index(self._m_Type) + self._m_Stage]
        self._m_HP = self._m_PrevHP
        self._m_Speed = speed
        if random_vector:
            vx, vy = random.randint(-10, 10), random.randint(-10, 10)
            while vx is 0 and vy is 0:
                vx, vy = random.randint(-10, 10), random.randint(-10, 10)
            self._m_DVector = Vector2D(vx, vy)
        else:
            self._m_DVector = Vector2D(-self._m_x, self.CLIENT_HEIGHT / 2 - self._m_y)
        self._m_DVector.normalize()
        self.CheckBox = \
            Rect(self._m_x - self._m_Image.w / 2, self._m_y - self._m_Image.h / 2,
                 self._m_x + self._m_Image.w / 2, self._m_y + self._m_Image.h / 2)
        self._m_Radian = 0.0
        self._m_HitTimer = 0.0
        self._m_BornTimer = 0.0

        # Set Boolean
        self._m_bEffect = False
        self._m_Hit = False
        self._m_Die = False

    def __del__(self):
        self.release()

    def update(self, TimeElapsed):
        if self._m_Die:
            pass  # TODO: 사망 후 스프라이트 or 알파값
            return None
        self._m_Die = self._m_HP <= 0
        if not self._m_bEffect and self._m_x - self._m_Image.w / 2 < self.CLIENT_WIDTH / 3:
            self._m_bEffect = True
        elif self._m_x - self._m_Image.w / 2 > self.CLIENT_WIDTH / 3 or self._m_DVector.x > 0:
            self._m_bEffect = False

        if self._m_bEffect:
            self._m_BornTimer += TimeElapsed
            if self._m_BornTimer > self.BORN_TIME:
                self._m_BornTimer -= self.BORN_TIME
                self._m_HP -= 1

        if self.check_hit():
            self._m_HitTimer += TimeElapsed
            self.CheckBox.set_parameter()
            if self._m_HitTimer > self.HIT_TIME:
                self._m_HitTimer = 0.0
                self._m_Hit = False
            return None
        else:
            self.CheckBox.set_parameter(
                self._m_x - self._m_Image.w / 2, self._m_y - self._m_Image.h / 2,
                self._m_x + self._m_Image.w / 2, self._m_y + self._m_Image.h / 2)
        self._m_EffectImage.update()
        self.move(TimeElapsed)
        self.bounce()

    def draw(self, purse_y):
        if self._m_Die:
            return None
        self._m_Image.rotate_draw(self._m_Radian, self._m_x, self._m_y + purse_y)
        if self._m_bEffect or self._m_Type is 'Boss':
            self._m_EffectImage.draw(self._m_x, self._m_y + purse_y)
        self.CheckBox.draw(purse_y)

    def get_type(self):
        return self._m_Type

    def get_pos(self):
        return self._m_x, self._m_y

    def get_hp(self):
        return self._m_HP

    def move(self, TimeElapsed):
        self._m_x += self._m_DVector.x * self._m_Speed * TimeElapsed
        self._m_y += self._m_DVector.y * self._m_Speed * TimeElapsed

        if self._m_Radian >= math.pi * 2:
            self._m_Radian = 0
        elif self._m_Type is not 'Boss':
            self._m_Radian += TimeElapsed
        elif self._m_Type is 'Boss':
            self._m_Radian += TimeElapsed * 10

    def bounce(self):
        if self._m_x > self.CLIENT_WIDTH * (3 / 2):
            if self._m_DVector.x > 0:
                self._m_DVector.x = -self._m_DVector.x
        if self._m_y > self.CLIENT_HEIGHT or self._m_y < 0:
            self._m_DVector.y = -self._m_DVector.y

    def crash_impact(self):
        return self._m_x - self._m_Image.w / 2 < self.CLIENT_WIDTH / 10

    def check_hit(self):
        if self._m_HP is not self._m_PrevHP:
            self._m_PrevHP = self._m_HP
            self._m_Hit = True
            # TODO: 피격 사운드 출력
        return self._m_Hit

    def hit(self, atk):
        if self._m_HP is self._m_PrevHP and self._m_HP > 0:
            self._m_HP -= atk

    def is_die(self):
        return self._m_Die

    def release(self):
        del self._m_EffectImage
        del self._m_Image
