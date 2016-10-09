from SpriteAnimation import*
import sdl2#

class Player:

    def __init__(self, x, y):
        self._m_Animation = SpriteAnimation()
        self._m_Animation.set_sprite('Resource\Graphics\Sprite\Player\Idle_Normal.png', 'Idle_Normal', 6)
        self._m_Animation.set_sprite('Resource\Graphics\Sprite\Player\MoveFront.png', 'MoveFront', 2)
        self._m_Animation.set_sprite('Resource\Graphics\Sprite\Player\MoveBack.png', 'MoveBack', 2)
        self._m_Animation.set_state('Idle_Normal', 6, 0, 6, 6, 6)
        self._m_Animation.set_state('MoveFront', 2, 0, 1, 2, 2)
        self._m_Animation.set_state('MoveBack', 2, 0, 1, 2, 2)
        self._m_Animation.set_state_delay('Idle_Normal', 6, 1, 1)
        self._m_Animation.set_state_delay('MoveFront', 5, 100, 1)
        self._m_Animation.set_state_delay('MoveBack', 5, 100, 1)

        self._m_x = x
        self._m_y = y
        self._m_bGameover = False
        self._m_bQuit = False

    def update(self, TimeElapsed):
        self._m_Animation.update()
        if self._m_Animation.get_current_state() is 'MoveFront':
            self._m_x += 1
        if self._m_Animation.get_current_state() is 'MoveBack':
            self._m_x -= 1

    def draw(self):
        self._m_Animation.draw(self._m_x, self._m_y)

    def release(self):
        del self._m_Animation

    def isGameover(self):
        return self._m_bGameover

    def isQuit(self):
        return self._m_bQuit

    def handle_events(self):
        events = get_events()
        for event in events:
            if event.type == SDL_QUIT:
                self._m_bQuit = True
            if event.type == SDL_KEYDOWN:
                if event.key == SDLK_LEFT:
                    self._m_Animation.update_state('MoveBack')
                elif event.key == SDLK_RIGHT:
                    self._m_Animation.update_state('MoveFront')
            elif event.type == SDL_KEYUP:
                self._m_Animation.update_state('Idle_Normal')
