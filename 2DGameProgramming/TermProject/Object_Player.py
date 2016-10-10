from SpriteAnimation import*


class Player:
    def __init__(self, x, y):
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
        self._m_Animation.set_state_delay('Attack_Punch', 5, 5, 5)

        # Set Character State
        self._m_x = x
        self._m_y = y
        self._m_Earth_HP = 100
        self._m_AtkBox = POINT()
        self._m_AtkBox.left = 0
        self._m_AtkBox.right = 0
        self._m_AtkBox.top = 0
        self._m_AtkBox.bottom = 0

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
        
        self._m_CommandTimer = 0.0

        # Flags
        self._m_bGameover = False
        self._m_bQuit = False
        self._m_bKeyDown = False

    def targeting(self, target):
        self._m_Target_List = target

    def update(self, TimeElapsed):
        if True not in self._m_KeyDown.values():
            self._m_Animation.update_state('Idle_Normal')
            for bList in self._m_AtkBox:
                self._m_AtkBox[bList] = 0
        else:
            self._move()
            self._attack()
        self._m_Animation.update()
        if self._m_Earth_HP <= 0:
            self._m_Earth_HP = 0
            self._m_bGameover = True

    def _move(self):
        if self._m_KeyDown.Right:
            self._m_Animation.update_state('MoveFront')
            self._m_x += 10
        if self._m_KeyDown.Up:
            self._m_Animation.update_state('MoveFront')
            self._m_y += 10
        if self._m_KeyDown.Left:
            self._m_Animation.update_state('MoveBack')
            self._m_x -= 10
        if self._m_KeyDown.Down:
            self._m_Animation.update_state('MoveBack')
            self._m_y -= 10

    def _attack(self):
        if self._m_KeyDown.Punch:
            self._m_Animation.update_state('Attack_Punch')
            self._m_AtkBox.right = self._m_x + self._m_Animation.get_currentimage_width() / 2
            self._m_AtkBox.top = self._m_y + self._m_Animation.get_currentimage_height() / 2
            self._m_AtkBox.left = self._m_x
            self._m_AtkBox.bottom = self._m_y - self._m_Animation.get_currentimage_height() / 2

    def draw(self):
        self._m_Animation.draw(self._m_x, self._m_y)

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

        if self._m_Keys[SDL_SCANCODE_UP] or self._m_Keys[SDL_SCANCODE_DOWN]:
            if self._m_Keys[SDL_SCANCODE_DOWN]:
                self._m_KeyDown.Up = False
                self._m_KeyDown.Down = True
                self._m_bKeyDown = True
            if self._m_Keys[SDL_SCANCODE_UP]:
                self._m_KeyDown.Down = False
                self._m_KeyDown.Up = True
                self._m_bKeyDown = True

        if self._m_Keys[SDL_SCANCODE_Z] or self._m_Keys[SDL_SCANCODE_X]:
            if self._m_Keys[SDL_SCANCODE_Z]:
                self._m_KeyDown.Kick = False
                self._m_KeyDown.Punch = True
                self._m_bKeyDown = True
            if self._m_Keys[SDL_SCANCODE_X]:
                self._m_KeyDown.Punch = False
                self._m_KeyDown.Kick = True
                self._m_bKeyDown = True

        if not self._m_bKeyDown:
            for bList in self._m_KeyDown:
                self._m_KeyDown[bList] = False

        events = get_events()
        for event in events:
            if event.type == SDL_QUIT:
                self._m_bQuit = True

