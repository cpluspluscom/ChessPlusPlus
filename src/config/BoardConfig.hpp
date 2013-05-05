#ifndef ChessPlusPlusBoardConfigurationManagerClass_HeaderPlusPlus
#define ChessPlusPlusBoardConfigurationManagerClass_HeaderPlusPlus

#include "Configuration.hpp"

namespace chesspp
{
    namespace config
    {
        class BoardConfig : public Configuration
        {
            std::string initial_layout;
            std::uint8_t board_width, board_height;
            std::uint16_t cell_width, cell_height;

        public:
            BoardConfig()
            : Configuration("config.json")
            , initial_layout(res_path + std::string(reader()["chesspp"]["board"]["initial_layout"]))
            , board_width                          (reader()["chesspp"]["board"]["width"]          )
            , board_height                         (reader()["chesspp"]["board"]["height"]         )
            , cell_width                           (reader()["chesspp"]["board"]["cell_width"]     )
            , cell_height                          (reader()["chesspp"]["board"]["cell_height"]    )
            {
            }

            std::string getInitialLayout() const noexcept { return initial_layout; }
            uint8_t     getBoardWidth   () const noexcept { return board_width;    }
            uint8_t     getBoardHeight  () const noexcept { return board_height;   }
            uint16_t    getCellWidth    () const noexcept { return cell_width;     }
            uint16_t    getCellHeight   () const noexcept { return cell_height;    }
        };
    }
}

#endif
