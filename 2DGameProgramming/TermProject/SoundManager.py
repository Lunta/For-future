import pygame


class SoundManager:
    def __init__(self):
        pygame.mixer.init()
        self.BGM_Play = pygame.mixer.Sound('Resource\Sound\BGM\Play.ogg')
        self.SE_Punch = pygame.mixer.Sound('Resource\Sound\Effect\Punch.ogg')
        #self.SE_Kick = pygame.mixer.Sound('Resource\Sound\Effect\Kick.mp3')
        #self.SE_Kamehameha = pygame.mixer.Sound('Resource\Sound\Effect\Kamehameha.mp3')
        #self.SE_PowerUp_Sound = pygame.mixer.Sound('Resource\Sound\Effect\PowerUp_Sound.mp3')
        #self.SE_PowerUp = pygame.mixer.Sound('Resource\Sound\Effect\PowerUp.mp3')
        #self.SE_PowerUp2 = pygame.mixer.Sound('Resource\Sound\Effect\PowerUp2.mp3')
        #self.SE_Move = pygame.mixer.Sound('Resource\Sound\Effect\Move.mp3')
        self.SE_Boss_Crashed = pygame.mixer.Sound('Resource\Sound\Effect\Boss_Crashed.ogg')
        self.SE_Crash_Impact = pygame.mixer.Sound('Resource\Sound\Effect\Crash_Impact.ogg')
        self.SE_Meteor_Crashed = pygame.mixer.Sound('Resource\Sound\Effect\Meteor_Crashed.ogg')







