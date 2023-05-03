//Standard Libraries//
#include <list>
#include <map>
#include <stack>
#include <vector>
#include <math.h>
#include <cstring>
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <typeinfo>
using namespace std;

//Libraries//
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

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
#include "Animation.h"
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

