#pragma once
class ColliderComponent
{
public:
  ColliderComponent();
  virtual ~ColliderComponent();

  virtual bool intersectsCollider(ColliderComponent* collider) = 0;
  virtual ColliderComponent* clone() = 0;
};

