from SpriteAnimation import*


class Player:
    def __init__(self, sound_manager, x, y):
        # Set Player Animation
        self._m_Animation = SpriteAnimation()
        self._m_Animation.set_sprite('Resource\Graphics\Sprite\Player\Idle_Normal.png', 'Idle_Normal', 6)
        self._m_Animation.set_sprite('Resource\Graphics\Sprite\Player\MoveFront.png', 'MoveFront', 2)
        self._m_Animation.set_sprite('Resource\Graphics\Sprite\Player\MoveBack.png', 'MoveBack', 2)
        self._m_Animation.set_sprite('Resource\Graphics\Sprite\Player\Attack_Punch.png', 'Attack_Punch', 4)
        # Set Animation State
        self._m_Animation.set_state('Idle_Normal', 6, 0, 6, 6, 6)
        self._m_Animation.set_state('MoveFront', 2, 0, 1, 2, 2)
        self._m_Animation.set_state('MoveBack', 2, 0, 1, 2, 2)
        self._m_Animation.set_state('Attack_Punch', 4, 0, 1, 2, 4)
        # Set Animation Delay
        self._m_Animation.set_state_delay('Idle_Normal', 6, 1, 1)
        self._m_Animation.set_state_delay('MoveFront', 5, 100, 1)
        self._m_Animation.set_state_delay('MoveBack', 5, 100, 1)
        self._m_Animation.set_state_delay('Attack_Punch', 3, 3, 3)

        # Set SoundManager
        self._m_SoundManager = sound_manager

        # Set Character State TODO: 캐릭터 파라미터 밸런스 조절
        self._m_x = x
        self._m_y = y
        self._m_atk = 1
        self._m_move_speed = 10
        self._m_Earth_HP = 100
        self._m_AtkBox = Rect()

        # Target
        self._m_Target_List = None

        # Input Control
        self._m_Keys = None
        self._m_KeyDown = POINT()
        self._m_KeyDown.Left = False
        self._m_KeyDown.Right = False
        self._m_KeyDown.Down = False
        self._m_KeyDown.Up = False
        self._m_KeyDown.Punch = False  # Z key
        self._m_KeyDown.Kick = False  # X key

        # Timer
        self.STATE_RESET_TIME = 0.4
        self.CRASHED_STOP_TIME = 0.03
        self._m_CommandTimer = 0.0
        self._m_StateTimer = 0.0
        self._m_CrashTimer = 0.0

        # Flags
        self._m_Crash = False
        self._m_SoundOutput = False
        self._m_bKeyDown = False
        self._m_bGameover = False
        self._m_bQuit = False

    def targeting(self, target):
        self._m_Target_List = target

    def update(self, TimeElapsed):
        self._m_StateTimer += TimeElapsed
        if True not in self._m_KeyDown.values() or self._m_StateTimer > 0.5:
            self._m_StateTimer = 0.0
            self._m_Animation.update_state('Idle_Normal')
            self._m_AtkBox.set_parameter()
        else:
            if self.crash_check():
                self._m_CrashTimer += TimeElapsed
                if self._m_CrashTimer > self.CRASHED_STOP_TIME:
                    self._m_CrashTimer = 0.0
                    self._m_Crash = False
                return None
            self._move()
            self._attack()
        self._m_Animation.update()
        if self._m_Earth_HP <= 0:
            self._m_Earth_HP = 0
            self._m_bGameover = True

    def _move(self):
        if 'Attack' in self._m_Animation.get_current_state():
            self._m_KeyDown.Right = False
            self._m_KeyDown.Left = False
            self._m_KeyDown.Up = False
            self._m_KeyDown.Down = False
            return None

        if self._m_KeyDown.Right:
            self._m_Animation.update_state('MoveFront')
            self._m_x += self._m_move_speed
        if self._m_KeyDown.Up:
            self._m_Animation.update_state('MoveFront')
            self._m_y += self._m_move_speed
        if self._m_KeyDown.Left:
            self._m_Animation.update_state('MoveBack')
            self._m_x -= self._m_move_speed
        if self._m_KeyDown.Down:
            self._m_Animation.update_state('MoveBack')
            self._m_y -= self._m_move_speed

    def _attack(self):
        if not self._m_KeyDown.Punch and not self._m_KeyDown.Kick:
            return None

        if self._m_Animation.get_current_state() is 'Attack_Punch' and \
                self._m_Animation.get_current_state_state() is self._m_Animation.StateState.action and \
                not self._m_SoundOutput:
            #self._m_SoundManager.SE_Punch.play()
            self._m_SoundOutput = True
        elif self._m_Animation.get_current_state_state() is self._m_Animation.StateState.execute:
            self._m_SoundOutput = False

        if self._m_KeyDown.Punch:
            self._m_Animation.update_state('Attack_Punch')
            self._m_AtkBox.set_parameter(
                self._m_x, self._m_y - self._m_Animation.get_currentimage_height() / 4,
                self._m_x + self._m_Animation.get_currentimage_width() / 2,
                self._m_y + self._m_Animation.get_currentimage_height() / 2)
            self._m_KeyDown.Punch = False

    def crash_check(self):
        if self._m_Target_List.CheckBox.bottom < self._m_y < self._m_Target_List.CheckBox.top and \
                self._m_Target_List.CheckBox.left < self._m_x < self._m_Target_List.CheckBox.right - \
                (self._m_Target_List.CheckBox.right - self._m_Target_List.CheckBox.left) / 2:
            self._m_x = self._m_Target_List.CheckBox.left
        if self._m_Target_List.CheckBox.bottom < self._m_y < self._m_Target_List.CheckBox.top and \
                self._m_Target_List.CheckBox.left + \
                (self._m_Target_List.CheckBox.right - self._m_Target_List.CheckBox.left) / 2 < \
                self._m_x < self._m_Target_List.CheckBox.right:
            self._m_x = self._m_Target_List.CheckBox.right

        if 'Attack' not in self._m_Animation.get_current_state():
            return False

        if not self._m_Crash and check_rect_crash(self._m_AtkBox, self._m_Target_List.CheckBox) and \
                self._m_Animation.get_current_state_state() is self._m_Animation.StateState.action:
            self._m_Crash = True
            self._m_Target_List.hit(self._m_atk)
            self._m_SoundManager.SE_Punch.play()
        return self._m_Crash

    def draw(self, purse_y):
        self._m_Animation.draw(self._m_x, self._m_y + purse_y)
        self._m_AtkBox.draw(purse_y)

    def release(self):
        self._m_Animation.release()
        del self._m_Animation

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
            if self._m_Keys[SDL_SCANCODE_Z]:
                self._m_KeyDown.Kick = False
                self._m_KeyDown.Punch = True
                self._m_bKeyDown = True
            if self._m_Keys[SDL_SCANCODE_X]:
                self._m_KeyDown.Punch = False
                self._m_KeyDown.Kick = True
                self._m_bKeyDown = True
        else:
            self._m_KeyDown.Punch = False
            self._m_KeyDown.Kick = False

        if not self._m_bKeyDown:
            for bList in self._m_KeyDown:
                self._m_KeyDown[bList] = False

        events = get_events()
        for event in events:
            if event.type == SDL_QUIT:
                self._m_bQuit = True

