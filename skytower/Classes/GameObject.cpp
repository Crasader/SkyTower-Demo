#include "GameObject.h"


GameObject::GameObject(GraphicComponent* graphic, PhysicComponent* physic, ColliderComponent* collider, InputComponent* input)
  : graphic_(std::shared_ptr<GraphicComponent>(graphic)),
  physic_(std::shared_ptr<PhysicComponent>(physic)),
  collider_(std::shared_ptr<ColliderComponent>(collider)),
  input_(std::shared_ptr<InputComponent>(input)) 
{
}


GameObject::~GameObject()
{
  if (graphic_) {
    graphic_->getNode()->removeFromParent();
  }
}


GameObject * GameObject::clone()
{
  GraphicComponent*  graphic = nullptr;
  PhysicComponent*   physic = nullptr;
  InputComponent*    input = nullptr;
  ColliderComponent* collider = nullptr;

  if (input_) { 
    input = input_->clone();
  }

  if (physic_) {
    physic = physic_->clone();
  }

  if (graphic_) {
    graphic = graphic_->clone();
  }

  if (collider_) {
    collider = collider_->clone();
  }

  //create clone of GameObject
  auto object = new GameObject(graphic, physic, collider, input);

  //clone some variables
  object->setTag(tag_);

  return object ;
}


void GameObject::update(float deltaTime)
{
  if (input_) {
    input_->update(this);
  }


  if (physic_) {
    physic_->update(this, deltaTime);
  }

  if (graphic_) {
    graphic_->update(this);
  }

}

void GameObject::fixedUpdate(float deltaTime)
{
  if (physic_) {
    physic_->fixedUpdate(this, deltaTime);
  }
}

bool GameObject::intersectsObject(std::shared_ptr<GameObject> gameObject)
{
  //Assume that all objects are round
  const float reduceBy = 0.0f;
  auto pos1 = getGraphic()->getPosition();
  auto pos2 = gameObject->getGraphic()->getPosition();
  auto size1 = getGraphic()->getNode()->getBoundingBox().size;
  auto size2 = gameObject->getGraphic()->getNode()->getBoundingBox().size;
  auto squaredRadius1 = std::pow(std::min(size1.width, size1.height) / 2, 2);
  auto squaredRadius2 = std::pow(std::min(size2.width, size2.height) / 2, 2);
  auto len1 = std::abs(pos1.x - pos2.x);
  auto len2 = std::abs(pos1.y - pos2.y);
  auto squaredDistance = len1 * len1 + len2 * len2;
  
  bool objectsIntersects = (squaredDistance <= (squaredRadius1 + squaredRadius2 - reduceBy));
  return objectsIntersects;
}


std::shared_ptr<InputComponent> GameObject::getInput()
{
  return input_;
}

std::shared_ptr<PhysicComponent> GameObject::getPhysic()
{
  return physic_;
}

std::shared_ptr<GraphicComponent> GameObject::getGraphic()
{
  return graphic_;
}

std::shared_ptr<ColliderComponent> GameObject::getCollider()
{
  return collider_;
}

void GameObject::setInput(InputComponent* input)
{
  input_ = std::shared_ptr<InputComponent>(input);
}

void GameObject::setPhysic(PhysicComponent* physic)
{
  physic_ = std::shared_ptr<PhysicComponent>(physic);
}

void GameObject::setGraphic(GraphicComponent* graphic)
{
  graphic_ = std::shared_ptr<GraphicComponent>(graphic);
}

void GameObject::setCollider(ColliderComponent* collider)
{
  collider_ = std::shared_ptr<ColliderComponent>(collider);
}


std::shared_ptr<GameObject> GameObject::getChild()
{
  return child_;
}


inline void GameObject::setTag(int tag)
{
  tag_ = tag;
}


int GameObject::getTag()
{
  return tag_;
}


void GameObject::setChild(GameObject* gameObject)
{
  child_ = std::shared_ptr<GameObject>(gameObject);

  bool childNodeAndParentNodeExists = child_->getGraphic() && graphic_;
  if (childNodeAndParentNodeExists) {
    child_->getGraphic()->setParentNode(graphic_->getNode());
  }
}
