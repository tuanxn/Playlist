// Playlist

#include <iostream>
#include "Playlist.h"
#include <string>
#include <sstream>


using namespace std;

int main() {
	Playlist test = Playlist();
}

// Song_Entry method definitions

bool Playlist::Song_Entry::set_id(int id) {
	if (!(id >= 0))
		return false;
	_id = id;
	return true;
}

bool Playlist::Song_Entry::set_name(string name) {
	if (name.empty())
		return false;
	_name = name;
	return true;
}

// Node Constructor TODO

Playlist::Node::~Node() {
	_next->_next = nullptr;
	delete _next;
	// TODO
}

Playlist::Playlist() {
	Node* temp = new Node(Song_Entry(-1, "HEAD"));
	_head = temp;
	_tail = temp;
	_prev_to_current = temp;
	_size = 0;
}

Playlist::~Playlist() {
	delete _head;
}

Playlist* Playlist::insert_at_cursor(const Song_Entry& s) {
	Node* newNode = new Node(s);
	_prev_to_current->insert_next(newNode);
	_size++;
	return this;
}

Playlist* Playlist::push_back(const Song_Entry& s) {
	Node* original = _prev_to_current;
	_prev_to_current = _tail;
	insert_at_cursor(s);
	_tail = _prev_to_current->get_next();
	_prev_to_current = original;
	return this;
}

Playlist* Playlist::push_front(const Song_Entry& s) {
	Node* original = _prev_to_current;
	_prev_to_current = _head;
	insert_at_cursor(s);
	_prev_to_current = original;
	return this;
}

Playlist* Playlist::advance_cursor() {
	if (_prev_to_current->get_next() == _tail) {
		return nullptr;
	}
	_prev_to_current = _prev_to_current->get_next();
	return this;
}

Playlist* Playlist::circular_advance_cursor() {
	if (_prev_to_current->get_next() == _tail) {
		_prev_to_current = _head;
		return this;
	}
	_prev_to_current = _prev_to_current->get_next();
	return this;
}

Playlist::Song_Entry& Playlist::get_current_song() const {
	if (_prev_to_current->get_next() != nullptr) {
		return _prev_to_current->get_next()->get_song();
	}
	return this->_head->get_next()->get_song();
}

Playlist* Playlist::remove_at_cursor() {
	// TODO
	Node* removedNode = _prev_to_current->get_next();
	_prev_to_current->remove_next();
	_size--;
	return this;
}

Playlist* Playlist::rewind() {
	_prev_to_current = _head;
	return this;
}

Playlist* Playlist::clear() {
	size_t total = _size;
	_prev_to_current = _head;
	for (size_t i = 0; i < total; i++) {
		if (!(_prev_to_current->get_next() == nullptr)) {
			remove_at_cursor();
		}
	}
	_prev_to_current = _head;
	_tail = _head;

	// get location that head is pointing to and set to nullptr
	Node* temp = _head->get_next();
	temp = nullptr;
	return this;
}

Playlist::Song_Entry& Playlist::find_by_id(int id) const {
	Node* temp = _head;

	for (size_t i = 0; i < _size; i++) {
		if (temp->get_next() == nullptr) {
			return this->_head->get_song();
		}
		if (temp->get_next()->get_song().get_id() == id) {
			return temp->get_next()->get_song();
		}
		else {
			temp = temp->get_next();
		}
	}
	return this->_head->get_song();
}

Playlist::Song_Entry& Playlist::find_by_name(string songName) const {
	Node* temp = _head;

	for (size_t i = 0; i < _size; i++) {
		if (temp->get_next() == nullptr) {
			return this->_head->get_song();
		}
		if (temp->get_next()->get_song().get_name() == songName) {
			return temp->get_next()->get_song();
		}
		else {
			temp = temp->get_next();
		}
	}
	return this->_head->get_song();
}

string Playlist::to_string() const {

	static int unsigned MAX_LINES = 25;

	string output = "Playlist: " + std::to_string(_size) + " entries.\n";
	Node* temp = _head;
	int count = 0;
	while (temp->get_next() != nullptr) {

		count++;

		output += "{ id: " + std::to_string(temp->get_next()->get_song().get_id()) + ", name: " + temp->get_next()->get_song().get_name() + " }";

		if (temp == _prev_to_current) {
			output += " [P]";
		}
		if (temp == _tail) {
			output += " [T]";
		}
		if (count == 25) {
			output += "\n...";
			break;
		}

		output += "\n";

		temp = temp->get_next();

	}
	output += "\n";
	return output;
}
