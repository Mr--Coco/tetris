#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

void	set_pixel(SDL_Surface *surface, int x, int y, Uint32 color)
{
  *((Uint32*)(surface->pixels)+x+(y*surface->w)) = color;
}

Mix_Music	*set_music(char *str)
{
  Mix_Music	*music;

  if ((music = Mix_LoadMUS(str)) == NULL)
    {
      printf("%s\n", Mix_GetError());
      exit(EXIT_FAILURE);
    }
  if (Mix_PlayMusic(music, -1) == -1)
    {
      printf("%s\n", Mix_GetError());
      exit(EXIT_FAILURE);
    }
  return (music);
}

void		tetris(void)
{
  int		go;
  int		volume;
  SDL_Surface	*screen;
  SDL_Event	event;
  Mix_Music	*music;

  go = 1;
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  if ((screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    {
      printf("video mode failed\n");
      exit(EXIT_FAILURE);
    }
  SDL_WM_SetCaption("GRAPH", NULL);

  SDL_Flip(screen);
  if (Mix_OpenAudio(22050, AUDIO_S16, 2, 4096) == -1)
    {
      printf("%s\n", Mix_GetError());
      exit(EXIT_FAILURE);
    }
  music = set_music("gw2.wav");
  volume = Mix_VolumeMusic(-1);
  while (go)
    {
      SDL_WaitEvent(&event);
      switch (event.type)
	{
	case SDL_KEYDOWN:
	  switch (event.key.keysym.sym)
	    {
	    case SDLK_ESCAPE:
	      go = 0;
	      break;
	    case SDLK_SPACE:
	      if (Mix_VolumeMusic(-1) > 0)
		Mix_VolumeMusic(0);
	      else
		Mix_VolumeMusic(volume);
	      break;
	    case SDLK_LEFT:
	      if (volume - 10 > 0)
		Mix_VolumeMusic((volume = volume - 10));
	      break;
	    case SDLK_RIGHT:
	      if (volume + 10 < 128)
		Mix_VolumeMusic((volume = volume + 10));
	      break;
	    case SDLK_UP:
	      {
		Mix_FreeMusic(music);
		music = set_music("shit_gets_real.wav");
	      }
	      break;
	    case SDLK_DOWN:
	      {
		Mix_FreeMusic(music);
		music = set_music("call_me_maybe.wav");
	      }
	      break;
	    }
	  break;
	}
    }
  Mix_FreeMusic(music);
  Mix_CloseAudio();
  SDL_Quit();
}

int	main(int ac, char **av)
{
  if (ac == 1)
    tetris();
  else
    printf("./tetris\tWithout arguments\n");
  return (0);
}
