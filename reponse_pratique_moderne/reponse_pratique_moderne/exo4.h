#pragma once
#include <iostream>
#include <memory>

class Resource {
public:
    Resource(int id) : id_(id) {
        std::cout << "Resource " << id_ << " created" << std::endl;
    }

    ~Resource() {
        std::cout << "Resource " << id_ << " destroyed" << std::endl;
    }

    void use() { std::cout << "Using resource " << id_ << std::endl; }

private:
    int id_;
};

void processResource() {
    Resource* r1 = new Resource(1);
    //Modernisation 
    //std::unique_ptr<Resource> r1 = std::make_unique<Resource>(Resource(1));

    Resource* r2 = new Resource(2);
    //Modernisation 
    //std::unique_ptr<Resource> r2 = std::make_unique<Resource>(Resource(2));
    try {
        r2->use();
        // Simulation d’une erreur
        throw std::runtime_error("Error occurred");
    }
    catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
        //Modernisation
        //Plus necessaire donc commenter ou supprimer la ligne qui suit
        delete r2;
    }

    r1->use();
    //Modernisation
    //Plus necessaire donc commenter ou supprimer la ligne qui suit
    delete r1;
}

