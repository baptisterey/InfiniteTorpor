#include "GenerateLevel.h"



GenerateLevel::GenerateLevel(GameObject * game_object) : Renderer(game_object)
{
	setLayer(50);
}


GenerateLevel::~GenerateLevel()
{
}

void GenerateLevel::start()
{
	srand(seed);
	generateLevel();
}

void GenerateLevel::render()
{

	const int size = 50;


	//Draw the rects for testing
	for (Room* room : rooms_vector) {
		SDL_Rect rect;
		rect.w = size;
		rect.h = size;

		rect.x = room->getGridPos().x * size * 1.2f;
		rect.y = room->getGridPos().y * size * 1.2f;

		int r, g, b;

		if (room->getRoomType() == Room::StartRoom) {
			r = 0;
			g = 255;
			b = 0;
		}
		else if (room->getRoomType() == Room::EndRoom) {
			r = 0;
			g = 0;
			b = 255;
		}
		else {
			r = 255;
			g = 0;
			b = 0;
		}
		TextureManager::DrawRect(rect, r, g, b, 255, true, false);

		//Draw the doors
		for (OwnMathFuncs::Vector2 door : room->getDoors()) {

			SDL_Rect door_rect;
			door_rect.w = size * 0.2;
			door_rect.h = size * 0.2;
			door_rect.x = rect.x + rect.w / 2;
			door_rect.y = rect.y + rect.h / 2;
			
			
			door_rect.x += door.x * (rect.w / 2);
			door_rect.y += door.y * (rect.h / 2);

			TextureManager::DrawRect(door_rect, 255, 255, 255, 255, true, false);
		}

	}

}

void GenerateLevel::clean()
{
	rooms[world_grid_size_x][world_grid_size_y];

	for (Room* room : rooms_vector) {
		delete room;
	}
	rooms_vector.clear();
	Renderer::clean();
}

void GenerateLevel::generateLevel()
{
	//init the first room at center
	OwnMathFuncs::Vector2 first_pos = {(float) world_grid_size_x / 2, (float) world_grid_size_y / 2 };

	pos_taken.push_back(first_pos);

	Room* first_room = new Room(first_pos);
	rooms[(int) first_pos.x][(int) first_pos.y] = first_room;
	rooms_vector.push_back(first_room);

	//magic number
	float random_to_compare = 0.55f;

	for (int i = 0; i < number_of_rooms; i++) {

		float r = ((float) rand() / (float) RAND_MAX);
		std::cout << r << std::endl;
		bool one_neighbour = r < random_to_compare ? true : false;
		
		OwnMathFuncs::Vector2 new_pos = { 0, 0 };
		int iteration = 0;

		do {

			new_pos = getNewPos();
			iteration++;

		} while ((one_neighbour && getNumberOfNeighbours(new_pos) > 1) && iteration < 100);
		
		Room* new_room = new Room(new_pos);
		rooms[(int)new_pos.x][(int)new_pos.y] = new_room;
		rooms_vector.push_back(new_room);
		pos_taken.push_back(new_pos);
	}

	//Set the start and the end of the level
	start_room = rooms_vector[0];
	end_room = rooms_vector[0];

	for(Room* room : rooms_vector){

		//test for start room & end room
		if (start_room == nullptr || (room->getGridPos().x + room->getGridPos().y) <= (start_room->getGridPos().x + start_room->getGridPos().y)) {
			start_room = room;
		}
		else if (end_room == nullptr || (room->getGridPos().x + room->getGridPos().y) >(end_room->getGridPos().x + end_room->getGridPos().y)) {
			end_room = room;
		}
		

		//set the doors
		int x = room->getGridPos().x - 1;
		int y = room->getGridPos().y;

		if (x > 0 && x < GenerateLevel::world_grid_size_x && y > 0 && y < GenerateLevel::world_grid_size_y && rooms[x][y] != nullptr) {
			room->addDoor({ -1, 0 });
		}

		x = room->getGridPos().x + 1;
		y = room->getGridPos().y;

		if (x > 0 && x < GenerateLevel::world_grid_size_x && y > 0 && y < GenerateLevel::world_grid_size_y && rooms[x][y] != nullptr) {
			room->addDoor({ 1, 0 });
		}

		x = room->getGridPos().x;
		y = room->getGridPos().y - 1;

		if (x > 0 && x < GenerateLevel::world_grid_size_x && y > 0 && y < GenerateLevel::world_grid_size_y && rooms[x][y] != nullptr) {
			room->addDoor({ 0, -1 });
		}

		x = room->getGridPos().x;
		y = room->getGridPos().y + 1;

		if (x > 0 && x < GenerateLevel::world_grid_size_x && y > 0 && y < GenerateLevel::world_grid_size_y && rooms[x][y] != nullptr) {
			room->addDoor({ 0, 1 });
		}

	}

	start_room->setRoomType(Room::StartRoom);
	end_room->setRoomType(Room::EndRoom);
}

int GenerateLevel::getNumberOfNeighbours(OwnMathFuncs::Vector2 room_pos)
{
	int i = 0;
	bool is_ok = false;
	
	std::cout << "zsadza" << std::endl;

	Room* room = rooms[(int) room_pos.x][(int) room_pos.y];

	if (room != nullptr) {

		int x = room->getGridPos().x - 1;
		int y = room->getGridPos().y;

		if (x > 0 && x < GenerateLevel::world_grid_size_x && y > 0 && y < GenerateLevel::world_grid_size_y && rooms[x][y] != nullptr) {
			i++;
		}

		x = room->getGridPos().x + 1;
		y = room->getGridPos().y;

		if (x > 0 && x < GenerateLevel::world_grid_size_x && y > 0 && y < GenerateLevel::world_grid_size_y && rooms[x][y] != nullptr) {
			i++;
		}

		x = room->getGridPos().x;
		y = room->getGridPos().y - 1;

		if (x > 0 && x < GenerateLevel::world_grid_size_x && y > 0 && y < GenerateLevel::world_grid_size_y && rooms[x][y] != nullptr) {
			i++;
		}

		x = room->getGridPos().x;
		y = room->getGridPos().y + 1;

		if (x > 0 && x < GenerateLevel::world_grid_size_x && y > 0 && y < GenerateLevel::world_grid_size_y && rooms[x][y] != nullptr) {
			i++;
		}
	}

	return i;
}

OwnMathFuncs::Vector2 GenerateLevel::getNewPos()
{
	bool pos_ok = true;
	int x, y;
	OwnMathFuncs::Vector2 checking_pos = { 0, 0 };

	do {
		//------- GETTING A POS ---------

		//Get a random existing pos
		OwnMathFuncs::Vector2 random_existing_pos = pos_taken.at((int)rand() % (pos_taken.size()));

		x = random_existing_pos.x;
		y = random_existing_pos.y;

		int random_x_or_y = rand() % 2;

		if (random_x_or_y == 0) {
			int random_x = rand() % 2;
			if (random_x == 0) {
				x = random_existing_pos.x + 1;
			}
			else {
				x = random_existing_pos.x - 1;
			}
		}
		else {
			int random_y = rand() % 2;
			if (random_y == 0) {
				y = random_existing_pos.y + 1;
			}
			else {
				y = random_existing_pos.y - 1;
			}
		}
		checking_pos = { (float)x , (float)y };


		//We check if the pos is not already taken
		pos_ok = true;
		for (OwnMathFuncs::Vector2 pos : pos_taken) {
			if (pos == checking_pos) {
				pos_ok = false;
			}
		}

	} while (!pos_ok || x < 0 || x > world_grid_size_x || y < 0 || y > world_grid_size_y);


	return checking_pos;
}