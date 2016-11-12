from SpriteAnimation import*


class Player:
    def __init__(self, client_width, client_height, image_manager, sound_manager, x, y):
        # Set Client Size
        self.CLIENT_WIDTH = client_width
        self.CLIENT_HEIGHT = client_height

        # Set Player Animation
        self._m_Animation_Normal = image_manager.Animation_Player
        self._m_Animation_PowerUp = image_manager.Animation_Player_PowerUp
        self._m_Animation = self._m_Animation_Normal

        # Set Effect
        self._m_Attack_Effect = image_manager.SpriteImage_PlayerEffect_Attack
        self._m_PowerUp_Effect = image_manager.SpriteImage_PlayerEffect_PowerUp
        self._m_PowerUp2_Effect = image_manager.SpriteImage_PlayerEffect_PowerUp2
        self._m_Kamehameha = image_manager.SpriteImage_PlayerEffect_Kamehameha

        # Set Image
        self._m_UI_Box = image_manager.Image_UI_Box

        # Set SoundManager
        self.SoundManager = sound_manager

        # Set UI Font
        self.OutPut_Font = Font('Resource\Font\Typo_DecoSolidSlash.ttf', 60)

        # Set Character Parameter TODO: 캐릭터 파라미터 밸런스 조절
        self._m_x = x
        self._m_y = y
        self._m_move_speed = 350
        self._m_Earth_HP = 100
        self._m_PrevHP = self._m_Earth_HP
        self._m_AtkBox = Rect()
        self.ATK = 1
        self.Shake_Earth = 1

        # Set UI Parameter
        self.Score = 0
        self.GameTimer = 0.0
        self.PowerGauge = 0

        # Target
        self._m_Target_List = None
        self._m_Item_List = None

        # Input Control
        self._m_Keys = None
        self._m_KeyDown = POINT()
        self._m_KeyDown.Left = False
        self._m_KeyDown.Right = False
        self._m_KeyDown.Down = False
        self._m_KeyDown.Up = False
        self._m_KeyDown.Punch = False  # Z key
        self._m_KeyDown.Kick = False  # X key

        # Combo Control
        self._m_KindOfAttack = POINT()
        self._m_KindOfAttack.Not_Attack = 0
        self._m_KindOfAttack.Punch = 1
        self._m_KindOfAttack.Punch_2 = 2
        self._m_KindOfAttack.Kick = 3
        self._m_Attack_prevState = None

        # Timer
        self.STATE_RESET_TIME = 0.4
        self.CRASHED_STOP_TIME = 0.03
        self.ITEM_POWER_DOWN_TIME = 20
        self.SWITCH_POWER_TIME = 0.5
        self._m_CommandTimer = 0.0
        self._m_StateTimer = 0.0
        self._m_CrashTimer = 0.0
        self._m_PowerDownTimer = 0.0
        self._m_SwitchPowerTimer = 0.0

        # Flags
        self._m_Crash = False
        self._m_Effect = False
        self._m_PowerUp = False
        self._m_PowerUp_Update = False
        self._m_PowerUp_Sound = False
        self._m_Hit = False
        self._m_SoundOutput = False
        self._m_bKeyDown = False
        self._m_bGameover = False
        self._m_bQuit = False

    def targeting(self, target, item):
        self._m_Target_List = target
        self._m_Item_List = item

    def update(self, TimeElapsed):
        self.update_ui(TimeElapsed)
        self._m_StateTimer += TimeElapsed
        if True not in self._m_KeyDown.values() or self._m_StateTimer > 0.5:
            self.reset_state()
        else:
            self.get_item_check()
            self._m_Attack_Effect.update()
            if self.crash_check():
                self._m_CrashTimer += TimeElapsed
                if self._m_CrashTimer > self.CRASHED_STOP_TIME:
                    self._m_CrashTimer = 0.0
                    self._m_Crash = False
                return None
            self._move(TimeElapsed)
            self._attack()
        self._m_Animation.update()

    def update_ui(self, TimeElapsed):
        self.GameTimer += TimeElapsed
        self._m_PowerDownTimer += TimeElapsed
        self.PowerGauge = 100 - (100 * self._m_PowerDownTimer) / self.ITEM_POWER_DOWN_TIME
        if self._m_PowerDownTimer > self.ITEM_POWER_DOWN_TIME:
            self._m_PowerDownTimer -= self.ITEM_POWER_DOWN_TIME
            self.ATK = max(self.ATK - 1, 1)
        elif self.ATK is 1:
            self._m_PowerUp_Update = False
            self._m_PowerDownTimer = 0
            self.PowerGauge = 0.0
            if self._m_Animation is self._m_Animation_PowerUp:
                if self._m_PowerUp:
                    self._m_Animation.update_state('PowerDown')
                    self.SoundManager.SE_PowerUp.stop()
                    self.SoundManager.SE_PowerUp2.stop()
                    self._m_PowerUp = False
                self._m_SwitchPowerTimer += TimeElapsed
                if self._m_SwitchPowerTimer > self.SWITCH_POWER_TIME:
                    self._m_SwitchPowerTimer = 0.0
                    self._m_Animation = self._m_Animation_Normal

        if self.ATK > 1:
            self._m_PowerUp_Effect.update()
            if self._m_Animation is self._m_Animation_Normal:
                if not self._m_PowerUp:
                    self._m_Animation.update_state('PowerUp')
                    self._m_Animation.update_state('PowerUp')
                    self.SoundManager.SE_PowerUp_Sound.play()
                    self.SoundManager.SE_PowerUp.play(-1)
                    self._m_PowerUp = True
                self._m_SwitchPowerTimer += TimeElapsed
                if self._m_SwitchPowerTimer > self.SWITCH_POWER_TIME:
                    self._m_SwitchPowerTimer = 0.0
                    self._m_Animation = self._m_Animation_PowerUp

        if self.ATK > 2:
            if not self._m_PowerUp_Sound:
                self.SoundManager.SE_PowerUp.stop()
                self.SoundManager.SE_PowerUp2.play(-1)
                self._m_PowerUp_Sound = True
            if not self._m_PowerUp_Update:
                self._m_PowerUp2_Effect.update()
                self._m_PowerUp_Update = True
            else:
                self._m_PowerUp_Update = False
        elif self.ATK is 2:
            if self._m_PowerUp_Sound:
                self.SoundManager.SE_PowerUp.play(-1)
                self.SoundManager.SE_PowerUp2.stop()
                self._m_PowerUp_Sound = False

        if self._m_Earth_HP <= 0:
            self._m_Earth_HP = 0
            self._m_bGameover = True

    def reset_state(self):
        self._m_StateTimer = 0.0
        self._m_Animation.update_state('Idle_Normal')
        self._m_AtkBox.set_parameter()
        self._m_Effect = False

    def _move(self, TimeElapsed):
        if 'Attack' in self._m_Animation.get_current_state():
            self._m_KeyDown.Right = False
            self._m_KeyDown.Left = False
            self._m_KeyDown.Up = False
            self._m_KeyDown.Down = False
            return None

        if self._m_KeyDown.Right:
            self._m_Animation.update_state('MoveFront')
            self._m_x += self._m_move_speed * TimeElapsed
        if self._m_KeyDown.Up:
            self._m_Animation.update_state('MoveFront')
            self._m_y += self._m_move_speed * TimeElapsed
        if self._m_KeyDown.Left:
            self._m_Animation.update_state('MoveBack')
            self._m_x -= self._m_move_speed * TimeElapsed
        if self._m_KeyDown.Down:
            self._m_Animation.update_state('MoveBack')
            self._m_y -= self._m_move_speed * TimeElapsed

    def _attack(self):
        if not self._m_KeyDown.Punch and not self._m_KeyDown.Kick:
            return None

        if self._m_Animation.get_current_state() is 'Attack_Punch' and \
                self._m_Animation.get_current_state_state() is self._m_Animation.StateState.action and \
                not self._m_SoundOutput:
            self._m_SoundOutput = True
        elif self._m_Animation.get_current_state_state() is self._m_Animation.StateState.execute:
            self._m_SoundOutput = False

        if self._m_KeyDown.Punch:
            if self._m_Attack_prevState is self._m_KindOfAttack.Punch:
                self._m_Animation.update_state('Attack_Punch_2')
                self._m_Attack_prevState = self._m_KindOfAttack.Punch_2
            else:
                self._m_Animation.update_state('Attack_Punch')
                self._m_Attack_prevState = self._m_KindOfAttack.Punch
            self._m_AtkBox.set_parameter(
                self._m_x, self._m_y - self._m_Animation.get_currentimage_height() / 4,
                self._m_x + self._m_Animation.get_currentimage_width() / 2,
                self._m_y + self._m_Animation.get_currentimage_height() / 2)
            self._m_KeyDown.Punch = False
        if self._m_KeyDown.Kick:
            self._m_Animation.update_state('Attack_Kick')
            self._m_Attack_prevState = self._m_KindOfAttack.Kick
            self._m_AtkBox.set_parameter(
                self._m_x, self._m_y - self._m_Animation.get_currentimage_height() / 4,
                self._m_x + self._m_Animation.get_currentimage_width() / 2,
                self._m_y + self._m_Animation.get_currentimage_height() / 2)

    def crash_check(self):
        for Target in self._m_Target_List:
            if Target.CheckBox.bottom < self._m_y < Target.CheckBox.top and \
                    Target.CheckBox.left < self._m_x < Target.CheckBox.right - \
                    (Target.CheckBox.right - Target.CheckBox.left) / 2:
                self._m_x -= 5
            if Target.CheckBox.bottom < self._m_y < Target.CheckBox.top and Target.CheckBox.left + \
                    (Target.CheckBox.right - Target.CheckBox.left) / 2 < self._m_x < Target.CheckBox.right:
                self._m_x += 5

        if 'Attack' not in self._m_Animation.get_current_state():
            return False
        for Target in self._m_Target_List:
            if not self._m_Crash and check_rect_crash(self._m_AtkBox, Target.CheckBox) and \
                    self._m_Animation.get_current_state_state() is self._m_Animation.StateState.action:
                self._m_Crash = True
                Target.hit(self.ATK)
                self.Score += self.ATK * 10
                self._m_Effect = True
                if 'Kick' in self._m_Animation.get_current_state():
                    self.SoundManager.SE_Kick.play()
                else:
                    self.SoundManager.SE_Punch.play()
        return self._m_Crash

    def check_hit_earth(self):
        self._m_Hit = False
        if self._m_Earth_HP is not self._m_PrevHP:
            self.Shake_Earth = self._m_PrevHP - self._m_Earth_HP
            self._m_PrevHP = self._m_Earth_HP
            self._m_Hit = True
        else:
            self.Shake_Earth = 1
        return self._m_Hit

    def hit(self, atk):
        if self._m_Earth_HP is self._m_PrevHP and self._m_Earth_HP > 0:
            self._m_Earth_HP -= atk

    def get_item_check(self):
        for item in self._m_Item_List:
            if check_rect_crash(
                    Rect(self._m_x - self._m_Animation.get_currentimage_width() / 2,
                         self._m_y - self._m_Animation.get_currentimage_height() / 2,
                         self._m_x + self._m_Animation.get_currentimage_width() / 2,
                         self._m_y + self._m_Animation.get_currentimage_height() / 2),
                    item.CheckBox):
                item.use()
                self.ATK += 1

    def draw(self, purse_y):
        if self.ATK > 1:
            self._m_PowerUp_Effect.draw(self._m_x, self._m_y + purse_y + 20)
        self._m_Animation.draw(self._m_x, self._m_y + purse_y)
        if self.ATK > 2:
            self._m_PowerUp2_Effect.draw(self._m_x, self._m_y + purse_y)
        if self._m_Effect:
            self._m_Attack_Effect.draw(
                self._m_x + self._m_Animation.get_currentimage_width() / 2 + random.randint(-15, 15),
                self._m_y + purse_y + self._m_Animation.get_currentimage_height() / 4 + random.randint(-40, 30))

        # Draw UI
        self._m_AtkBox.draw(purse_y)
        self._m_UI_Box.draw(self.CLIENT_WIDTH / 6 - 10, self.CLIENT_HEIGHT - 55)
        self.OutPut_Font.draw(10, self.CLIENT_HEIGHT - 25, 'Score : %d' % self.Score, (255, 255, 255))
        self.OutPut_Font.draw(10, self.CLIENT_HEIGHT - 75,
                              'Power : %.2f' % (self.PowerGauge + 100 * (self.ATK - 1)) + '%', (255, 255, 255))
        self.OutPut_Font.draw(10, self.CLIENT_HEIGHT - 125,
                              'People : %d' % self._m_Earth_HP + '%', (255, 255, 255))
        self.OutPut_Font.draw(self.CLIENT_WIDTH * 2 / 5 + 20, self.CLIENT_HEIGHT - 20,
                              'Time: %.2f' % self.GameTimer, (255, 255, 255))

    def release(self):
        self._m_Animation_Normal.release()
        self._m_Animation_PowerUp.release()
        del self._m_Animation_Normal
        del self._m_Animation_PowerUp

    def isGameover(self):
        return self._m_bGameover

    def isQuit(self):
        return self._m_bQuit

    def handle_events(self):
        self._m_Keys = SDL_GetKeyboardState(None)

        self._m_bKeyDown = False

        if self._m_Keys[SDL_SCANCODE_LEFT] or self._m_Keys[SDL_SCANCODE_RIGHT]:
            if self._m_Keys[SDL_SCANCODE_LEFT]:
                self._m_KeyDown.Right = False
                self._m_KeyDown.Left = True
                self._m_bKeyDown = True
            if self._m_Keys[SDL_SCANCODE_RIGHT]:
                self._m_KeyDown.Left = False
                self._m_KeyDown.Right = True
                self._m_bKeyDown = True
        else:
            self._m_KeyDown.Left = False
            self._m_KeyDown.Right = False

        if self._m_Keys[SDL_SCANCODE_UP] or self._m_Keys[SDL_SCANCODE_DOWN]:
            if self._m_Keys[SDL_SCANCODE_DOWN]:
                self._m_KeyDown.Up = False
                self._m_KeyDown.Down = True
                self._m_bKeyDown = True
            if self._m_Keys[SDL_SCANCODE_UP]:
                self._m_KeyDown.Down = False
                self._m_KeyDown.Up = True
                self._m_bKeyDown = True
        else:
            self._m_KeyDown.Down = False
            self._m_KeyDown.Up = False

        if self._m_Keys[SDL_SCANCODE_Z] or self._m_Keys[SDL_SCANCODE_X]:
            if self._m_Keys[SDL_SCANCODE_X]:
                self._m_KeyDown.Punch = False
                self._m_KeyDown.Kick = True
                self._m_bKeyDown = True
            if self._m_Keys[SDL_SCANCODE_Z]:
                self._m_KeyDown.Kick = False
                self._m_KeyDown.Punch = True
                self._m_bKeyDown = True
        else:
            self._m_KeyDown.Punch = False
            self._m_KeyDown.Kick = False

        #if not self._m_bKeyDown:
        #    for bList in self._m_KeyDown:
        #        self._m_KeyDown[bList] = False

        events = get_events()
        for event in events:
            if event.type == SDL_QUIT:
                self._m_bQuit = True

