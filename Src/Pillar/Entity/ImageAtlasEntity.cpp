/*
 * This source file is part of Pillar, the C++ Cross-platform middleware for game
 *
 * For the latest information, see https://github.com/prophecy/Pillar
 *
 * The MIT License (MIT)
 * Copyright (c) 2015 Adawat Chanchua
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "ImageAtlasEntity.h"
#include "json.h"
#include "../Florist/Florist.h"

using namespace std;
using namespace Json;

void ImageAtlasEntity::LoadJsonDataFormat(std::string name)
{
	// Set current atlas name
	_atlasName = name;

	// Clear map
	_spriteRects.clear();

	// String to store content
	char* document = NULL;

	// Load JSON from file
	SDL_RWops* file = SDL_RWFromFile(name.c_str(), "r");

	Sint64 sz = file->size(file);

	if (file != NULL)
	{
		// Allocate buffer
		document = (char*)malloc((size_t)sz);

		// Read
		if (SDL_RWread(file, document, (size_t)sz, 1) > 0)
		{
			DebugLog("Read JSON from: " + name + " has been finished");
		}

		// Close file
		SDL_RWclose(file);
	}

	// Parse it to concrete structure
	Value root;   // will contains the root value after parsing.
	Reader reader;
	bool parsingSuccessful = reader.parse(document, root);

	// Free document
	free(document);
	document = NULL;

	if (!parsingSuccessful)
	{
		// report to the user the failure and their locations in the document.
		DebugLog("Failed to parse configuration\n" + reader.getFormattedErrorMessages());

		return;
	}

	/* // frames's schema
	"attack_crouch (1).png":
	{
		"frame": {"x":2,"y":2,"w":143,"h":133},
		"rotated": false,
		"trimmed": true,
		"spriteSourceSize": {"x":12,"y":16,"w":143,"h":133},
		"sourceSize": {"w":170,"h":150},
		"pivot": {"x":0.5,"y":0.5}
	},
	*/

	// Parse
	Value frames = root.get("frames", "{}");

	for (Json::ValueIterator itr = frames.begin(); itr != frames.end(); itr++)
	{
		// Parse key and value
		Value key = itr.key();
		Value value = frames[key.asString()];

		// Parse frame
		Value frame = value["frame"];
		rect2f rect;
		rect.origin.data()[0] = frame["x"].asFloat();
		rect.origin.data()[1] = frame["y"].asFloat();
		rect.size.data()[0] = frame["w"].asFloat();
		rect.size.data()[1] = frame["h"].asFloat();

		_spriteRects.insert(pair<string, rect2f>(key.asString(), rect));
	}
}

void ImageAtlasEntity::SetCurrentFrame(std::string frameName)
{
	if (_spriteRects.count(frameName) == 0)
	{
		DebugLog(frameName + " does not exist in atlas name: " + _atlasName);
		return;
	}

	spriteRectCurrent = _spriteRects[frameName];
}