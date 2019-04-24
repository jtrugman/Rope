#pragma once

class Data;

class Observer {
public:
	virtual void update() = 0;
	virtual void update(Data*) = 0;
	virtual ~Observer();
};

class Data {
private:
	std::vector<Observer*> observers;
public:
	Data() {}
	void addObserver(Observer* obs) {
		observers.push_back(obs);
	}

	void removeObserver(Observer* obs) {
		//TODO:
	}

	void changed() const {
		for (auto obs : observers)
			obs->update();
	}
	void ichanged() const {
		for (auto obs : observers)
			obs->update(this);
	}
}
