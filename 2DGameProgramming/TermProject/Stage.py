from Object_Meteor import *
from Object_Item import *
from Utility import *


class Stage:
    Type = Meteor.TypeList

    def __init__(self, win_width, win_height, image_manager, sound_manager):
        self.ImageManager = image_manager
        self.SoundManager = sound_manager
        self.WINDOW_WIDTH = win_width
        self.WINDOW_HEIGHT = win_height
        self.POP_TIME = 4
        self.BOSS_POP_TIME = 50

        self._m_Timer = 0.0
        self._m_BossTimer = 0.0
        self._m_BossStage = 0
        self._m_BossList = \
            [
                Meteor(self.ImageManager, self.WINDOW_WIDTH * (3 / 2), self.WINDOW_HEIGHT / 2, 30, 'Boss',
                       self.WINDOW_WIDTH, self.WINDOW_HEIGHT, False, 0),
                Meteor(self.ImageManager, self.WINDOW_WIDTH * (3 / 2), self.WINDOW_HEIGHT / 2, 30, 'Boss',
                       self.WINDOW_WIDTH, self.WINDOW_HEIGHT, False, 1),
                Meteor(self.ImageManager, self.WINDOW_WIDTH * (3 / 2), self.WINDOW_HEIGHT / 2, 30, 'Boss',
                       self.WINDOW_WIDTH, self.WINDOW_HEIGHT, False, 2),
                Meteor(self.ImageManager, self.WINDOW_WIDTH * (3 / 2), self.WINDOW_HEIGHT / 2, 30, 'Boss',
                       self.WINDOW_WIDTH, self.WINDOW_HEIGHT, False, 3),
                Meteor(self.ImageManager, self.WINDOW_WIDTH * (3 / 2), self.WINDOW_HEIGHT / 2, 30, 'Boss',
                       self.WINDOW_WIDTH, self.WINDOW_HEIGHT, False, 4),
                Meteor(self.ImageManager, self.WINDOW_WIDTH * (3 / 2), self.WINDOW_HEIGHT / 2, 30, 'Boss',
                       self.WINDOW_WIDTH, self.WINDOW_HEIGHT, False, 5),
                Meteor(self.ImageManager, self.WINDOW_WIDTH * (3 / 2), self.WINDOW_HEIGHT / 2, 30, 'Boss',
                       self.WINDOW_WIDTH, self.WINDOW_HEIGHT, False, 6)
            ]


        self.Player = None
        self.MeteorList = []
        self.ItemList = []

    def build_object(self):
        pass

    def draw(self, purse_y):
        for meteor in self.MeteorList:
            meteor.draw(purse_y)
        for item in self.ItemList:
            item.draw(purse_y)

    def update(self, TimeElapsed):
        self._m_Timer += TimeElapsed
        self._m_BossTimer += TimeElapsed
        self.check_die()
        for meteor in self.MeteorList:
            meteor.update(TimeElapsed)
        for item in self.ItemList:
            item.update(TimeElapsed)
        if self._m_BossTimer > self.BOSS_POP_TIME + ((self.BOSS_POP_TIME / 2) * (self._m_BossStage + 1)):
            self._m_BossTimer = 0.0
            self.MeteorList.append(self._m_BossList[self._m_BossStage])
            self._m_BossStage += 1
        elif self._m_Timer > self.POP_TIME - (self._m_BossStage * 0.2):
            self._m_Timer -= (self.POP_TIME - (self._m_BossStage * 0.2))
            self.MeteorList.append(
                Meteor(self.ImageManager, self.WINDOW_WIDTH * (3 / 2), random.randint(0, self.WINDOW_HEIGHT),
                       random.randint(100, 150), self.Type[random.randint(0, 2)], self.WINDOW_WIDTH, self.WINDOW_HEIGHT))

    def check_die(self):
        for item in self.ItemList:
            if item.is_used():
                self.ItemList.remove(item)
        for meteor in self.MeteorList:
            if meteor.is_die():
                x, y = meteor.get_pos()
                if meteor.get_type() is not 'Small' and meteor.get_type() is not 'Boss':
                    for idx in range(random.randint(2, 4)):
                        self.MeteorList.append(
                            Meteor(self.ImageManager, x, y, random.randint(100, 150),
                                   self.Type[random.randint(0, self.Type.index(meteor.get_type()) - 1)],
                                   self.WINDOW_WIDTH, self.WINDOW_HEIGHT, True))
                    if random.randint(0, 7) is 0:
                        self.ItemList.append(Item(x, y, self.WINDOW_WIDTH, self.WINDOW_HEIGHT))
                elif meteor.get_type() is not 'Small' and meteor.get_type() is 'Boss':
                    for idx in range(random.randint(2, 4)):
                        self.MeteorList.append(
                            Meteor(self.ImageManager, x, y, random.randint(10, 100), 'Huge',
                                   self.WINDOW_WIDTH, self.WINDOW_HEIGHT, True))
                    self.ItemList.append(Item(x, y, self.WINDOW_WIDTH, self.WINDOW_HEIGHT))
                    self.SoundManager.SE_Boss_Crashed.play()
                self.SoundManager.SE_Meteor_Crashed.play()
                self.MeteorList.remove(meteor)
            if meteor.crash_impact():
                self.Player.hit(meteor.get_hp())
                self.SoundManager.SE_Crash_Impact.play()
                self.MeteorList.remove(meteor)

    def release(self):
        for meteor in self.MeteorList:
            meteor.release()
        del self.MeteorList



