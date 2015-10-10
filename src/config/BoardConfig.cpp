#include "BoardConfig.hpp"

namespace chesspp
{
    namespace config
    {
        BoardConfig::BoardConfig(ResourcesConfig &res)
        : Configuration{"config/chesspp/board.json"}
        , board_width  {reader()["board"]["width"]      }
        , board_height {reader()["board"]["height"]     }
        , cell_width   {reader()["board"]["cell width"] }
        , cell_height  {reader()["board"]["cell height"]}
        {
            auto pieces = reader()["board"]["pieces"];
            auto suits  = reader()["board"]["suits"];
            for(BoardSize_t r = 0; r < board_height; ++r)
            {
                for(BoardSize_t c = 0; c < board_width; ++c)
                {
                    auto piece = pieces[r][c];
                    auto suit  = suits [r][c];
                    if(piece.type() != util::JsonReader::Type::Null) //it is OK if suit is null
                    {
                        layout[{c, r}] = std::make_pair<PieceClass_t, SuitClass_t>(piece, suit);
                    }
                }
            }

            auto const &tex = res.setting("board", "pieces");
            for(auto const &suit : tex.object())
            {
                for(auto const &piece : suit.second.object())
                {
                    textures[suit.first][piece.first] = std::string(Textures_t::mapped_type::mapped_type(piece.second));
                }
            }
        }
    }
}
