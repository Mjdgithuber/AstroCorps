#include "TileMap.h"
#include "TilePackage.h"
#include "engine/common.h"
#include "engine/tools/xml/Register.h"
#include "engine/tools/xml/parsers/MapParser.h"
#include "engine/tools/managers/TextureManager.h"

/* =========================================================== */
/* ============== Constructors and Destructors =============== */
/* =========================================================== */

/* Makes a new empty tile map */
TileMap::TileMap()
	: m_rows(0), m_cols(0), m_bordered(false) {}

/* Deletes all entites */
TileMap::~TileMap() {
	for (unsigned int i = 0; i < m_entities.size(); i++)
		delete m_entities[i];
}

/* =========================================================== */
/* ======================== Functions ======================== */
/* =========================================================== */

/* Will draw all of the tiles and entities*/
void TileMap::draw_map(sf::RenderWindow& window) {
	// draw tiles
	for (unsigned int row = 0; row < m_rows; row++) {
		for (unsigned int col = 0; col < m_cols; col++)
			window.draw(m_tiles[row][col].get_sprite());
	}

	// draw entites
	for (Entity* e : m_entities)
		(*e).draw(window);
}

/* Will load a map file into the tile map */
void TileMap::load_map(const char* map_file) {
	// load map from xml file passed in
	TilePackage* tp = XML::load_map(map_file);

	// make sure tiles is empty
	m_tiles.clear();

	// save size data
	m_rows = tp->get_rows();
	m_cols = tp->get_cols();

	// get tile sheet ref for convenience
	const sf::Texture& tile_sheet = TextureManager::get_tile_sheet(Textures::TileSheet::MASTER_TILE_SHEET);

	// load the tile map
	m_tiles.reserve(m_rows);

	// global tile data
	float scale = Application::get_scale();
	unsigned int tile_size = Application::get_unscaled_tile_size();

	for (unsigned int r = 0; r < m_rows; r++) {
		std::vector<Tile> tile_col;
		tile_col.reserve(m_cols);
		for (unsigned int c = 0; c < m_cols; c++) {
			// get tile info from packet
			unsigned int reg_num = tp->get_register_num(c, r);
			unsigned int mod_num = tp->get_modifier_register_num(c, r);
			const std::string& script = tp->get_script(c, r);

			// get register information for texture location
			const Util::Point& location = Register::get_tilesheet_location(reg_num);

			// make a new tile
			Tile t(reg_num, mod_num, script);
			sf::Sprite& sp = t.get_sprite();
			sp.setTexture(tile_sheet);
			sp.setTextureRect(sf::IntRect(tile_size * (location.x * 2 + (m_bordered ? 1 : 0)), 0, tile_size, tile_size));
			sp.setScale(scale, scale);
			sp.setPosition(c * tile_size * scale, r * tile_size * scale);
			tile_col.push_back(t); // move semantics please
		}
		m_tiles.push_back(std::move(tile_col));
	}

	// free the tile package
	delete tp;
}

/* As of now updates the entities */
void TileMap::update(const sf::Time& delta_time) {
	for (Entity* e : m_entities)
		(*e).update(delta_time);
}

/* Adds an entity to the tile map */
Entity& TileMap::new_entity(const std::string& name, int x, int y, int width, int height) {
	m_entities.push_back(new Entity(name, ((unsigned int) m_entities.size()), x, y, width, height));
	// return newly created entity
	return (*m_entities.back());
}

/* Will reset all of the tile textures */
void TileMap::set_tile_textures() {
	LOG_TRACE("Setting the tile textures");

	// get tile size (to locate texture)
	unsigned int tile_size = Application::get_unscaled_tile_size();

	// loop though each tile by row
	for (unsigned int r = 0; r < m_rows; r++) {
		for (unsigned int c = 0; c < m_cols; c++) {
			// get the tile
			Tile& t = m_tiles[r][c];

			// get it's texture location
			const Util::Point& location = Register::get_tilesheet_location(t.get_register_number());

			// set the tile's texture
			t.get_sprite().setTextureRect(
				sf::IntRect(tile_size * (location.x * 2 + (m_bordered ? 1 : 0)),
					0, tile_size, tile_size));
		}
	}
}

/* Toggles the m_bordered bool and resets the textures */
void TileMap::toggle_borders() {
	LOG_TRACE("Toggling Borders!");
	m_bordered = !m_bordered;
	set_tile_textures();
}

/* ========================= Getters ========================= */

Tile& TileMap::get_tile(unsigned int row, unsigned int col) { return m_tiles[row][col]; }
const Tile& TileMap::get_tile(unsigned int row, unsigned int col) const { return m_tiles[row][col]; }

unsigned int TileMap::get_rows() const { return m_rows; }
unsigned int TileMap::get_cols() const { return m_cols; }