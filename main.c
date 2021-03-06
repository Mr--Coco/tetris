#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

static int	status = 1;
static int	pause = 1;

typedef struct	s_color
{
  int		r;
  int		g;
  int		b;
}		t_color;

typedef struct	s_point
{
  int		x_one;
  int		y_one;
  int		x_two;
  int		y_two;
}		t_point;

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

void		draw_vertical(SDL_Surface *screen, t_point *point, t_color *color)
{
  int		x_start;
  int		y_start;

  x_start = point->x_one;
  y_start = point->y_one;
  if (point->x_one == point->x_two)
    while (y_start < point->y_two)
      {
	set_pixel(screen, point->x_one, y_start, SDL_MapRGB(screen->format, color->r, color->g, color->b));
	y_start++;
      }
}

void		draw_horizontal(SDL_Surface *screen, t_point *point, t_color *color)
{
  int		x_start;
  int		y_start;

  x_start = point->x_one;
  y_start = point->y_one;
  if (point->y_one == point->y_two)
    while (x_start < point->x_two)
      {
	set_pixel(screen, x_start, point->y_one, SDL_MapRGB(screen->format, color->r, color->g, color->b));
	x_start++;
      }
}

void		fill_point(t_point *point, int x_one, int y_one, int x_two, int y_two)
{
  point->x_one = x_one;
  point->y_one = y_one;
  point->x_two = x_two;
  point->y_two = y_two;
}

void		fill_color(t_color *color, int r, int g, int b)
{
  color->r = r;
  color->g = g;
  color->b = b;
}

/*
** Dessine le rectangle de jeu
*/

void		draw_game_square(SDL_Surface *screen)
{
  t_point	point;
  t_color	color;

  fill_color(&color, 255, 255, 255);
  fill_point(&point, 20, 20, 20, 580);
  draw_vertical(screen, &point, &color);
  fill_point(&point, 420, 20, 420, 580);
  draw_vertical(screen, &point, &color);
  fill_point(&point, 20, 20, 420, 20);
  draw_horizontal(screen, &point, &color);
  fill_point(&point, 20, 580, 420, 580);
  draw_horizontal(screen, &point, &color);
}

/*
** Dessine le rectangle où la prochaine pièce s'affiche
*/

void		draw_next_figure_square(SDL_Surface *screen)
{
  t_point	point;
  t_color	color;

  fill_color(&color, 255, 255, 255);
  fill_point(&point, 440, 20, 440, 170);
  draw_vertical(screen, &point, &color);
  fill_point(&point, 780, 20, 780, 170);
  draw_vertical(screen, &point, &color);
  fill_point(&point, 440, 20, 780, 20);
  draw_horizontal(screen, &point, &color);
  fill_point(&point, 440, 170, 780, 170);
  draw_horizontal(screen, &point, &color);
}

/*
** Dessine les 3 lignes de niveau, score, ligne
*/

void		draw_information_square(SDL_Surface *screen, TTF_Font *police)
{
  t_point	point;
  t_color	color;
  SDL_Color	black_color = {255, 255, 255};
  SDL_Surface	*text;
  SDL_Rect	pos;

  fill_color(&color, 255, 255, 255);
  fill_point(&point, 440, 190, 440, 340);
  draw_vertical(screen, &point, &color);
  fill_point(&point, 780, 190, 780, 340);
  draw_vertical(screen, &point, &color);
  fill_point(&point, 440, 190, 780, 190);
  draw_horizontal(screen, &point, &color);
  fill_point(&point, 440, 340, 780, 340);
  draw_horizontal(screen, &point, &color);
  fill_point(&point, 440, 240, 780, 240);
  draw_horizontal(screen, &point, &color);
  fill_point(&point, 440, 290, 780, 290);
  draw_horizontal(screen, &point, &color);
  text = TTF_RenderText_Solid(police, "level", black_color);
  pos.x = 445;
  pos.y = 191;
  SDL_BlitSurface(text, NULL, screen, &pos);
  text = TTF_RenderText_Solid(police, "score", black_color);
  pos.x = 445;
  pos.y = 241;
  SDL_BlitSurface(text, NULL, screen, &pos);
  text = TTF_RenderText_Solid(police, "lines", black_color);
  pos.x = 445;
  pos.y = 291;
  SDL_BlitSurface(text, NULL, screen, &pos);
}

/*
** Dessine les boutons pause et mute
*/

void		draw_mute_pause_square(SDL_Surface *screen)
{
  t_point	point;
  t_color	color;
  SDL_Surface	*image;
  SDL_Rect	pos;

  fill_color(&color, 255, 255, 255);
  fill_point(&point, 490, 360, 490, 460);
  draw_vertical(screen, &point, &color);
  fill_point(&point, 710, 360, 710, 460);
  draw_vertical(screen, &point, &color);
  fill_point(&point, 490, 360, 710, 360);
  draw_horizontal(screen, &point, &color);
  fill_point(&point, 490, 460, 710, 460);
  draw_horizontal(screen, &point, &color);
  pos.x = 491;
  pos.y = 361;
  if (status == 1)
    image = SDL_LoadBMP("sound_icon.bmp");
  else if (status == -1)
    image = SDL_LoadBMP("mute_icon.bmp");
  SDL_BlitSurface(image, NULL, screen, &pos);
  pos.x = 611;
  pos.y = 361;
  if (pause == 1)
    image = SDL_LoadBMP("pause_off.bmp");
  else if (pause == -1)
    image = SDL_LoadBMP("pause_on.bmp");
  SDL_BlitSurface(image, NULL, screen, &pos);
}

/*
** Dessine le logo tetris
*/

void		draw_logo(SDL_Surface *screen)
{
  SDL_Surface	*image;
  SDL_Rect	pos;

  pos.x = 530;
  pos.y = 480;
  image = SDL_LoadBMP("tetris.bmp");
  SDL_BlitSurface(image, NULL, screen, &pos);
}

/*
** Initialise l'affichage
*/

void		init_draw(SDL_Surface *screen, TTF_Font *police)
{
  draw_game_square(screen);
  draw_next_figure_square(screen);
  draw_information_square(screen, police);
  draw_mute_pause_square(screen);
  draw_logo(screen);
}

/*
** Dessine le menu de pause
*/

void		draw_pause_menu(SDL_Surface *screen)
{
}

void		tetris(void)
{
  int		go;
  int		volume;
  SDL_Surface	*screen;
  SDL_Event	event;
  Mix_Music	*music;
  TTF_Font	*police;

  go = 1;
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  TTF_Init();
  if ((screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    {
      printf("video mode failed\n");
      exit(EXIT_FAILURE);
    }
  SDL_WM_SetCaption("tetris_sm20", NULL);
  police = TTF_OpenFont("arial.ttf", 36);
  if (Mix_OpenAudio(22050, AUDIO_S16, 2, 4096) == -1)
    {
      printf("%s\n", Mix_GetError());
      exit(EXIT_FAILURE);
    }
  music = set_music("tetris.wav");
  volume = Mix_VolumeMusic(-1);
  Mix_VolumeMusic((volume = 50));
  while (go)
    {
      init_draw(screen, police);
      SDL_Flip(screen);
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
	      {
		status *= -1;
		if (Mix_VolumeMusic(-1) > 0)
		  Mix_VolumeMusic(0);
		else
		  Mix_VolumeMusic(volume);
	      }
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
		music = set_music("mario_invicible.wav");
	      }
	      break;
	    case SDLK_DOWN:
	      {
		Mix_FreeMusic(music);
		music = set_music("mario_underwater.wav");
	      }
	      break;
	    }
	  break;
	case SDL_MOUSEBUTTONUP:
	  {
	    if (event.button.button == SDL_BUTTON_LEFT)
	      if (event.button.x >= 490 && event.button.x <= 590 && event.button.y >= 360 && event.button.y <= 460)
		{
		  status *= -1;
		  if (Mix_VolumeMusic(-1) > 0)
		    Mix_VolumeMusic(0);
		  else
		    Mix_VolumeMusic(volume);
		}
	      else if (event.button.x >= 610 && event.button.x <= 710 && event.button.y >= 360 && event.button.y <= 460)
		{
		  pause *= -1;
		  draw_pause_menu(screen);
		}
	  }
	  break;
	}
    }
  Mix_FreeMusic(music);
  Mix_CloseAudio();
  TTF_CloseFont(police);
  TTF_Quit();
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
