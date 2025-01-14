#include "battle_game/core/units/BoobooTank.h"

#include "battle_game/core/bullets/bullets.h"
#include "battle_game/core/game_core.h"
#include "battle_game/graphics/graphics.h"

namespace battle_game::unit {

BoobooTank::BoobooTank(GameCore *game_core, uint32_t id, uint32_t player_id)
    : Tank(game_core, id, player_id) {
}

void BoobooTank::Update() {
  TankMove(3.0f, glm::radians(180.0f));
  TurretRotate();
  Fire();
}

void BoobooTank::Fire() {
  if (fire_count_down_) {
    fire_count_down_--;
  } else {
    auto player = game_core_->GetPlayer(player_id_);
    if (player) {
      auto &input_data = player->GetInputData();
      if (input_data.mouse_button_down[GLFW_MOUSE_BUTTON_LEFT]) {
          auto velocity = Rotate(glm::vec2{0.0f, 20.0f}, turret_rotation_ - glm::radians(30.0f));
        GenerateBullet<bullet::BoobooBullet>(
            position_ + Rotate({0.0f, 1.2f}, turret_rotation_),
            turret_rotation_ - glm::radians(30.0f), GetDamageScale(), velocity);
          velocity = Rotate(glm::vec2{0.0f, 20.0f}, turret_rotation_ + glm::radians(30.0f));
      GenerateBullet<bullet::BoobooBullet2>(
          position_ + Rotate({0.0f, 1.2f}, turret_rotation_),
          turret_rotation_ + glm::radians(30.0f), GetDamageScale(), velocity);
        fire_count_down_ = kTickPerSecond;  // Fire interval 1 second.
      }
    }
  }
}

const char *BoobooTank::UnitName() const {
  return "BoobooTank";
}

const char *BoobooTank::Author() const {
  return "TangLi";
}
}  // namespace battle_game::unit
