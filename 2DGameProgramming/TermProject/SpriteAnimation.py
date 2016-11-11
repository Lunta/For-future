from SpriteImage import*


class SpriteAnimation:
    def __init__(self):
        self._m_SpriteState_List = []
        self._m_SpriteImage_List = []

        self.StateState = POINT()
        self.StateState.execute = 0
        self.StateState.action = 1
        self.StateState.exit = 2

        self._m_StartEnd = POINT()
        self._m_StartEnd.start = 0
        self._m_StartEnd.end = 1

        self._m_MaxState = []
        self._m_StateDelay = []
        self._m_StateExecute = []
        self._m_StateAction = []
        self._m_StateExit = []

        self._m_CurrentState = None
        self._m_NextState = None
        self._m_DelayCount = 0

    def set_sprite(self, path, state_name, w=1, h=1):
        self._m_SpriteImage_List.append(SpriteImage(path, state_name, w, h))
        self._m_SpriteState_List.append(self._m_SpriteImage_List[-1].get_name())
        if state_name in 'Idle_Normal':
            self._m_CurrentState = self._m_SpriteImage_List[self._m_SpriteState_List.index(state_name)]
            self._m_NextState = self._m_CurrentState
        self._m_MaxState.append(0)
        self._m_StateDelay.append([0 for st in range(3)])
        self._m_StateExecute.append([0 for st in range(2)])
        self._m_StateAction.append([0 for st in range(2)])
        self._m_StateExit.append([0 for st in range(2)])

    def set_state(self, state_index, val, execute_start, execute_end, exit_start, exit_end):
        self._m_MaxState[self._m_SpriteState_List.index(state_index)] = val
        self._m_StateExecute[self._m_SpriteState_List.index(state_index)][self._m_StartEnd.start] = execute_start
        self._m_StateExecute[self._m_SpriteState_List.index(state_index)][self._m_StartEnd.end] = execute_end
        self._m_StateAction[self._m_SpriteState_List.index(state_index)][self._m_StartEnd.start] = execute_end
        self._m_StateAction[self._m_SpriteState_List.index(state_index)][self._m_StartEnd.end] = exit_start
        self._m_StateExit[self._m_SpriteState_List.index(state_index)][self._m_StartEnd.start] = exit_start
        self._m_StateExit[self._m_SpriteState_List.index(state_index)][self._m_StartEnd.end] = exit_end

    def set_state_delay(self, state_index, execute_delay, action_delay, exit_delay):
        self._m_StateDelay[self._m_SpriteState_List.index(state_index)][self.StateState.execute] = execute_delay
        self._m_StateDelay[self._m_SpriteState_List.index(state_index)][self.StateState.action] = action_delay
        self._m_StateDelay[self._m_SpriteState_List.index(state_index)][self.StateState.exit] = exit_delay

    def update_state(self, state_name):
        # 현재 상태와 동일하면 생략
        if self._m_CurrentState.get_name() is state_name:
            return None

        # 변신 중에는 상태 갱신 생략
        if 'Power' in self._m_CurrentState.get_name():
            self._m_NextState = self._m_SpriteImage_List[self._m_SpriteState_List.index('Idle_Normal')]
            return None

        # 공격 중에는 상태 갱신 생략
        if 'Attack' in self._m_CurrentState.get_name() and 'Power' not in state_name:
            self._m_NextState = self._m_SpriteImage_List[self._m_SpriteState_List.index('Idle_Normal')]
            return None

        # 현재 상태가 idle 이 아니고
        # 현재 진행중인 상태가 진입 상태일 경우
        # 퇴장 상태로 변경하지 않고 갱신
        if self.get_current_state_state() is self.StateState.execute:
            self._m_CurrentState.set_currentframe(self._m_StateExecute[self._m_SpriteState_List.index(state_name)][self._m_StartEnd.start])
            self._m_CurrentState = self._m_SpriteImage_List[self._m_SpriteState_List.index(state_name)]
        else:
            # 이미 퇴장중이면 취소
            if self.get_current_state_state() is self.StateState.exit:
                return None
            self._m_NextState = self._m_SpriteImage_List[self._m_SpriteState_List.index(state_name)]
            self._m_CurrentState.set_currentframe(self._m_StateExit[self._m_SpriteState_List.index(state_name)][self._m_StartEnd.start])

        # 딜레이 카운터 초기화
        self._m_DelayCount = 0

    def get_current_state(self):
        return self._m_CurrentState.get_name()

    def get_current_state_state(self):

        # 진입 상태로 초기화
        state_state = self.StateState.execute
        # 진행 상태보다 많이 진행하고 있는 경우
        if self._m_CurrentState.get_currentframe_x() >= \
                self._m_StateAction[self._m_SpriteState_List.index(self._m_CurrentState.get_name())][self._m_StartEnd.end]:
            state_state = self.StateState.exit
        # 진행상태일 경우
        elif self._m_CurrentState.get_currentframe_x() >= \
                self._m_StateAction[self._m_SpriteState_List.index(self._m_CurrentState.get_name())][self._m_StartEnd.start]:
            state_state = self.StateState.action
        return state_state

    def get_currentimage_width(self):
        return self._m_CurrentState.get_frame_width()

    def get_currentimage_height(self):
        return self._m_CurrentState.get_frame_height()

    def update(self):
        # execute - action - exit
        state_state = self.get_current_state_state()

        # 딜레이 카운터 갱신
        self._m_DelayCount = (self._m_DelayCount + 1) % \
            self._m_StateDelay[self._m_SpriteState_List.index(self._m_CurrentState.get_name())][state_state]

        # 딜레이 카운터로 갱신 여부 확인
        if self._m_DelayCount is not 0:
            return None

        # 이미지 갱신
        self._m_CurrentState.update()
        # 초기화 되었을 경우 다음 상태로 변경
        if self._m_CurrentState.get_currentframe_x() is 0:
            self._m_CurrentState = self._m_NextState
            self._m_CurrentState.set_currentframe(
                self._m_StateExecute[self._m_SpriteState_List.index(self._m_CurrentState.get_name())][self._m_StartEnd.start])

    def draw(self, x, y):
        self._m_CurrentState.draw(x, y)

    def release(self):
        del self._m_SpriteState_List
        del self._m_SpriteImage_List
        del self._m_StartEnd
        del self._m_MaxState
        del self._m_StateDelay
        del self._m_StateExecute
        del self._m_StateAction
        del self._m_StateExit
        del self._m_CurrentState
        del self._m_NextState
        del self.StateState
