#pragma once

//Standard Libraries//
#include <windows.h>
#include <list>
#include <map>
#include <stack>
#include <vector>
#include <math.h>
#include <cstring>
#include <string>
#include <time.h>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <typeinfo>

using namespace std;

//Libraries//
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
using namespace glm;

#include "TimerDelegate.h"
#include "Timer.h"
#include "TrackAction.h"
#include "KeyFrameDelegate.h"
#include "KeyFrame.h"
#include "TrackDelegate.h"
#include "Track.h"

#include "EntityDelegate.h"
#include "SpriteDelegate.h"
#include "SoundDelegate.h"

#include "Texture.h"
#include "TextureManager.h"
#include "Transformation.h"
#include "Mechanics.h"
#include "FSMState.h"
#include "GraphicElement.h"
#include "HitBox.h"
#include "Sprite.h"

#include "GameObject.h"
#include "Entity.h"

#include "BufferObject.h"
#include "RenderBuffer.h"
#include "PixelBuffer.h"
#include "PackBuffer.h"
#include "UnpackBuffer.h"
#include "FeedbackBuffer.h"
#include "TextureBuffer.h"
#include "FrameBuffer.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "UniformBuffer.h"
#include "IndexBuffer.h"
#include "TileMapManager.h"
#include "ObjectManager.h"
#include "SoundManager.h"
#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"
#include "Game.h"
#include "EventManager.h"
