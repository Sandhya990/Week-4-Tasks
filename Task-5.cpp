#include <iostream>  
#include <vector>  
#include <string>  
#include <memory>  
#include <algorithm>  

// Singleton Pattern  
class HMISystem {
private:
    // Private constructor  
    HMISystem() {}

    // Static instance pointer  
    static HMISystem* instance;

public:
    // Public static method to get the instance  
    static HMISystem* getInstance() {
        if (instance == nullptr) {
            instance = new HMISystem();
        }
        return instance;
    }

    void displayState() {
        std::cout << "Current HMI State" << std::endl;
    }
};

// Initialize the static instance pointer  
HMISystem* HMISystem::instance = nullptr;

// Factory Pattern  
class Control {
public:
    virtual void render() = 0;
    virtual ~Control() = default;
};

class Button : public Control {
public:
    void render() override {
        std::cout << "Rendering Button" << std::endl;
    }
};

class Slider : public Control {
public:
    void render() override {
        std::cout << "Rendering Slider" << std::endl;
    }
};

class ControlFactory {
public:
    enum class ControlType { Button, Slider };

    static std::unique_ptr<Control> createControl(ControlType type) {
        switch (type) {
        case ControlType::Button: return std::make_unique<Button>();
        case ControlType::Slider: return std::make_unique<Slider>();
        default: return nullptr;
        }
    }
};

// Observer Pattern  
class ModeObserver {
public:
    virtual void update(const std::string& mode) = 0;
    virtual ~ModeObserver() = default;
};

class ModeSubject {
private:
    std::vector<ModeObserver*> observers;
    std::string mode;

public:
    void attach(ModeObserver* observer) {
        observers.push_back(observer);
    }

    void detach(ModeObserver* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void setMode(const std::string& newMode) {
        mode = newMode;
        notify();
    }

    void notify() {
        for (auto observer : observers) {
            observer->update(mode);
        }
    }
};

// Concrete observer example  
class ButtonObserver : public ModeObserver {
public:
    void update(const std::string& mode) override {
        if (mode == "Night") {
            std::cout << "Button visibility adjusted for Night mode." << std::endl;
        }
        else {
            std::cout << "Button visibility adjusted for Day mode." << std::endl;
        }
    }
};

// Strategy Pattern  
class RenderingStrategy {
public:
    virtual void render() = 0;
    virtual ~RenderingStrategy() = default;
};

class TwoDRendering : public RenderingStrategy {
public:
    void render() override {
        std::cout << "Rendering in 2D" << std::endl;
    }
};

class ThreeDRendering : public RenderingStrategy {
public:
    void render() override {
        std::cout << "Rendering in 3D" << std::endl;
    }
};

class HMIContext {
private:
    RenderingStrategy* strategy;

public:
    HMIContext(RenderingStrategy* strategy) : strategy(strategy) {}

    void setStrategy(RenderingStrategy* newStrategy) {
        strategy = newStrategy;
    }

    void render() {
        strategy->render();
    }
};

// Main function to demonstrate all patterns  
int main() {
    // Singleton Usage  
    HMISystem* hmi = HMISystem::getInstance();
    hmi->displayState();

    // Factory Usage  
    auto button = ControlFactory::createControl(ControlFactory::ControlType::Button);
    auto slider = ControlFactory::createControl(ControlFactory::ControlType::Slider);
    button->render();
    slider->render();

    // Observer Usage  
    ModeSubject modeSubject;
    ButtonObserver buttonObserver;

    modeSubject.attach(&buttonObserver);
    modeSubject.setMode("Day");
    modeSubject.setMode("Night");

    // Strategy Usage  
    HMIContext context(new TwoDRendering());
    context.render();

    context.setStrategy(new ThreeDRendering());
    context.render();

    return 0;
}