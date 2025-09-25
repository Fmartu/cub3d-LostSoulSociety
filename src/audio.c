/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:44:46 by fabi              #+#    #+#             */
/*   Updated: 2025/09/15 17:44:15 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../include/cube3d.h"
#include <stddef.h>

void	init_audio(t_game *game)
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		return ;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		return ;
	game->audio.background_music = Mix_LoadMUS("audio/background.wav");
	game->audio.end_music = Mix_LoadMUS("audio/endmusic.wav");
	game->audio.door_sound = Mix_LoadWAV("audio/dooropen.wav");
}

void	cleanup_audio(t_game *game)
{
	if (game->audio.background_music)
		Mix_FreeMusic(game->audio.background_music);
	if (game->audio.end_music)
		Mix_FreeMusic(game->audio.end_music);
	if (game->audio.door_sound)
		Mix_FreeChunk(game->audio.door_sound);
	Mix_CloseAudio();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

void	play_background_music(t_game *game)
{
	if (game->audio.background_music && !Mix_PlayingMusic())
		Mix_PlayMusic(game->audio.background_music, -1);
}

void	play_end_music(t_game *game)
{
	if (game->audio.end_music)
	{
		Mix_HaltMusic();
		Mix_PlayMusic(game->audio.end_music, -1);
	}
}

void	play_door_sound(t_game *game)
{
	if (game->audio.door_sound)
		Mix_PlayChannel(-1, game->audio.door_sound, 0);
}
