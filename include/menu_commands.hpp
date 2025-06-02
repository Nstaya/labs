#pragma once

#include <string>
#include "storage.hpp"
#include <memory>

class MenuCommand;
using menu_command_ptr = std::shared_ptr<MenuCommand>;

class MenuCommand {
protected:
    std::string description_;
public:
    explicit MenuCommand(const std::string& description);
    virtual ~MenuCommand() = default;

    const std::string get_description() const;
    virtual void execute(ShapeStorage& storage) = 0;
};

class AddShapeCommand : public MenuCommand {
public:
    explicit AddShapeCommand(const std::string& description);
    void execute(ShapeStorage& storage) override;
};

class ShowShapesCommand : public MenuCommand {
public:
    explicit ShowShapesCommand(const std::string& description);
    void execute(ShapeStorage& storage) override;
};

class ShowPerimetersCommand : public MenuCommand {
public:
    explicit ShowPerimetersCommand(const std::string& description);
    void execute(ShapeStorage& storage) override;
};

class ShowSumOfPerimetersCommand : public MenuCommand {
public:
    explicit ShowSumOfPerimetersCommand(const std::string& description);
    void execute(ShapeStorage& storage) override;
};

class SortShapesCommand : public MenuCommand {
public:
    explicit SortShapesCommand(const std::string& description);
    void execute(ShapeStorage& storage) override;
};

class DeleteShapeByPositionCommand : public MenuCommand {
public:
    explicit DeleteShapeByPositionCommand(const std::string& description);
    void execute(ShapeStorage& storage) override;
};

class DeleteShapesByPerimeterCommand : public MenuCommand {
public:
    explicit DeleteShapesByPerimeterCommand(const std::string& description);
    void execute(ShapeStorage& storage) override;
};

class ExitCommand : public MenuCommand {
    bool& is_running_;
public:
    ExitCommand(const std::string& description, bool& is_running);
    void execute(ShapeStorage& storage) override;
};
