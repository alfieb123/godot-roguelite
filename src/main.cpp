#include "main.hpp"

#include "util/assert.hpp"
#include "util/conversions.hpp"
#include "util/engine.hpp"
#include "util/input.hpp"

namespace rl
{
    Main::Main()
    {
        scene::node::set_unique_name(this, "Main");
    }

    void Main::_ready()
    {
        resource::preload::scene<Level> level{ path::scene::Level1 };
        m_active_level = level.instantiate();
        runtime_assert(m_active_level != nullptr);

        resource::preload::scene<MainDialog> dialog{ path::ui::MainDialog };
        m_main_dialog = dialog.instantiate();
        runtime_assert(m_main_dialog != nullptr);

        this->apply_default_settings();

        runtime_assert(m_main_dialog != nullptr);
        if (m_main_dialog != nullptr)
        {
            m_canvas_layer = gdcast<godot::CanvasLayer>(
                m_main_dialog->find_child("MainCanvasLayer", true, false));

            runtime_assert(m_canvas_layer != nullptr);
            runtime_assert(m_active_level != nullptr);

            if (m_active_level != nullptr && m_canvas_layer != nullptr)
                m_canvas_layer->add_child(m_active_level);

            if (m_main_dialog != nullptr)
                this->add_child(m_main_dialog);
        }
    }

    void Main::apply_default_settings()
    {
        engine::set_fps(60);
        input::use_accumulated_inputs(false);

        if (not engine::editor_active())
            engine::root_window()->set_size({ 1920, 1080 });
    }
}
