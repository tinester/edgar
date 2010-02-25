/*
Copyright (C) 2009-2010 Parallel Realities

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "../headers.h"

#include "../graphics/animation.h"
#include "../audio/audio.h"
#include "../system/properties.h"
#include "../entity.h"
#include "../enemy/enemies.h"
#include "../system/error.h"

extern Entity *self;

static void wait(void);
static void touch(Entity *);

Entity *addSlimeContainer(int x, int y, char *name)
{
	Entity *e = getFreeEntity();

	if (e == NULL)
	{
		showErrorAndExit("No free slots to add a Slime Container");
	}

	loadProperties(name, e);

	e->x = x;
	e->y = y;

	e->type = KEY_ITEM;

	e->face = RIGHT;

	e->action = &wait;

	e->draw = &drawLoopingAnimationToMap;

	setEntityAnimation(e, STAND);

	e->thinkTime = 0;

	return e;
}

static void wait()
{
	Entity *e;

	if (self->active == FALSE && self->health == 1)
	{
		self->thinkTime--;

		if (self->thinkTime <= 0)
		{
			if (self->mental < 15)
			{
				e = addEnemy("enemy/red_baby_slime", 0, 0);

				e->x = self->startX;
				e->y = self->startY;

				e->mental = 1;

				self->mental++;
			}

			self->thinkTime = 60;
		}
	}

	self->touch = self->active == FALSE ? &touch : NULL;

	setEntityAnimation(self, self->active == FALSE ? STAND : WALK);
}

static void touch(Entity *other)
{
	pushEntity(other);
}
