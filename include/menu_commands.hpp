#pragma once

#include <string>
#include "storage.hpp"
#include <memory>

class MenuCommand;

using menu_command_ptr = std::shared_ptr<MenuCommand>;


class MenuCommand {
private:
    const std::string description_;
public:
    MenuCommand(const std::string& description);

    const std::string get_description() const;

    virtual void execute(ShapeStorage &storage) = 0;

    virtual ~MenuCommand() = default;
};

class AddShapeCommand : public MenuCommand {
public:
    AddShapeCommand(const std::string& description);

    void execute(ShapeStorage &storage) override;
};

class ShowShapesCommand : public MenuCommand {
public:
    ShowShapesCommand(const std::string& description);
    void execute(ShapeStorage &storage) override;

};

class DeleteShapeByPositionCommand : public MenuCommand {
public:
    DeleteShapeByPositionCommand(const std::string& description);

    void execute(ShapeStorage &storage) override;
};

class ExitCommand : public MenuCommand {
public:
    ExitCommand(const std::string& description);

    void execute(ShapeStorage &storage) override;
};