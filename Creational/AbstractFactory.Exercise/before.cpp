#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

#define MOTIF

enum class IconType {
    none,
    ok,
    cancel,
    warning,
    error
};

class Widget
{
public:
    virtual void draw() = 0;
    virtual ~Widget() = default;
};

class Button : public Widget
{
    std::string caption_;
    IconType icon_type_;

public:
    Button(const std::string& caption, IconType icon_type)
        : caption_{caption}
        , icon_type_{icon_type}
    {
    }

    std::string caption() const
    {
        return caption_;
    }

    IconType icon() const
    {
        return icon_type_;
    }
};

class Menu : public Widget
{
    std::string text_;

public:
    Menu(const std::string& text)
        : text_{text}
    {
    }

    std::string text() const
    {
        return text_;
    }
};

///////////////////////////////////////////
// Motif family

class MotifButton : public Button
{
public:
    using Button::Button;

    void draw() override
    {
        cout << "MotifButton [ " << caption() << " ]\n";
    }
};

class MotifMenu : public Menu
{
public:
    using Menu::Menu;

    void draw() override
    {
        cout << "MotifMenu { " << text() << " }\n";
    }
};

/////////////////////////////////
// Windows family

class WindowsButton : public Button
{
public:
    using Button::Button;

    void draw() override
    {
        cout << "WindowsButton [ " << caption() << " ]\n";
    }
};

class WindowsMenu : public Menu
{
public:
    using Menu::Menu;

    void draw() override
    {
        cout << "WindowsMenu { " << text() << " }\n";
    }
};

//////////////////////////////////////

// create an abstract factory for widgets
// and concrete factories for each family

class WidgetFactory
{
public:
    virtual std::unique_ptr<Button> create_button(const std::string& caption, IconType icon) = 0;
    virtual std::unique_ptr<Menu> create_menu(const std::string& text) = 0;
    virtual ~WidgetFactory() = default;
};

class MotifWidgetFactory : public WidgetFactory
{
public:
    std::unique_ptr<Button> create_button(const std::string& caption, IconType icon) override
    {
        return std::make_unique<MotifButton>(caption, icon);
    }
    
    std::unique_ptr<Menu> create_menu(const std::string& text) override
    {
        return std::make_unique<MotifMenu>(text);
    }
};

class WindowsWidgetFactory : public WidgetFactory
{
public:
    std::unique_ptr<Button> create_button(const std::string& caption, IconType icon) override
    {
        return std::make_unique<WindowsButton>(caption, icon);
    }   

    std::unique_ptr<Menu> create_menu(const std::string& text) override
    {
        return std::make_unique<WindowsMenu>(text);
    }
};

class Window
{
    std::vector<std::unique_ptr<Widget>> widgets;

public:
    void display() const
    {
        std::cout << "######################\n";
        for (const auto& w : widgets)
            w->draw();
        std::cout << "######################\n\n";
    }

    void add_widget(std::unique_ptr<Widget> widget)
    {
        widgets.push_back(std::move(widget));
    }
};

class WindowOne : public Window
{

public:
    WindowOne(WidgetFactory& factory)
    {
        add_widget(factory.create_button("OK", IconType::ok));
        add_widget(factory.create_menu("File"));
    }
};

class WindowTwo : public Window
{

public:
    WindowTwo(WidgetFactory& factory)
    {
        add_widget(factory.create_button("OK", IconType::ok));
        add_widget(factory.create_menu("File"));
    }
};

int main(void)
{
#ifdef MOTIF
    MotifWidgetFactory widget_factory;
#else
    WindowsWidgetFactory widget_factory;
#endif

    WindowOne w1(widget_factory);
    w1.display();

    WindowTwo w2(widget_factory);
    w2.display();
}
