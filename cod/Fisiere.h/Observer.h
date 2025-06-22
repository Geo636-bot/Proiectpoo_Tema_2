
#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include <memory>
#include <string>
#include <algorithm>

// Observer interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void notifica(const std::string& eveniment, const std::string& detalii) = 0;
};

// Subject interface
class Subject {
private:
    std::vector<std::weak_ptr<Observer>> observeri;

public:
    virtual ~Subject() = default;
    
    void adaugaObserver(std::weak_ptr<Observer> observer) {
        observeri.push_back(observer);
    }
    
    void stergeObserver(std::shared_ptr<Observer> observer) {
        observeri.erase(
            std::remove_if(observeri.begin(), observeri.end(),
                [&observer](const std::weak_ptr<Observer>& weak_obs) {
                    return weak_obs.expired() || weak_obs.lock() == observer;
                }),
            observeri.end()
        );
    }
    
protected:
    void notificaObserveri(const std::string& eveniment, const std::string& detalii) {
        // Cleanup expired observers
        observeri.erase(
            std::remove_if(observeri.begin(), observeri.end(),
                [](const std::weak_ptr<Observer>& weak_obs) {
                    return weak_obs.expired();
                }),
            observeri.end()
        );
        
        // Notify active observers
        for (auto& weak_obs : observeri) {
            if (auto obs = weak_obs.lock()) {
                obs->notifica(eveniment, detalii);
            }
        }
    }
};

// Concrete Observer pentru logging
class LogObserver : public Observer {
public:
    void notifica(const std::string& eveniment, const std::string& detalii) override {
        std::cout << "📝 LOG: " << eveniment << " - " << detalii << std::endl;
    }
};

// Concrete Observer pentru statistici
class StatisticsObserver : public Observer {
private:
    int numarEvenimente = 0;

public:
    void notifica(const std::string& eveniment, const std::string& detalii) override {
        ++numarEvenimente;
        std::cout << "📊 STATS: Eveniment #" << numarEvenimente 
                  << " - " << eveniment << std::endl;
    }
    
    int getNumarEvenimente() const { return numarEvenimente; }
};

#endif
