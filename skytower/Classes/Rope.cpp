#include "Rope.h"
#include "Spawner.h"
#include "Globals.h"

USING_NS_CC;

Rope::Rope(InputComponent* input, cocos2d::Node* gameLayer, std::list<std::shared_ptr<GameObject>>* objectsPool, std::shared_ptr<Mediator> mediator)
  :gameLayer_(gameLayer), pool_(objectsPool), Colleague(mediator)
{
  //Create rope
  auto draw = DrawNode::create();
  draw->drawSegment(Vec2(0, 0), Vec2(0, 200), 4.0f, Color4F::RED);
  draw->setContentSize(Size(4, 200));
  draw->setAnchorPoint(Vec2(0.5f, 1.0f));

  auto graphic = new GraphicComponent(draw);
  setGraphic(graphic);
  setTag(ROPE);
  setRotation(30.0f);

  setInput(input);

  //add childBoject - hat (hook)
  auto gameObject = Globals::spawner.spawn(Globals::elementHat);
  setChild(gameObject);
  ////create rotate action
  auto rotate = EaseInOut::create(RotateBy::create(3.0f, -60.0f), 2.0f);
  auto rotateRev = EaseInOut::create(RotateBy::create(3.0f, 60.0f), 2.0f);
  auto sequence = Sequence::create(rotate, rotateRev, nullptr);
  auto rotating = RepeatForever::create(sequence);
  auto move = MoveBy::create(2.0f, Vec2(0.0f, 20.0f));
  auto moveSequence = Sequence::create(move, move->reverse(), nullptr);
  auto moving = RepeatForever::create(moveSequence);
  getCocosNode()->runAction(rotating);
  getCocosNode()->runAction(moving);
  ////

}


Rope::~Rope()
{
}



void Rope::attachElement(std::shared_ptr<GameObject> element)
{
  attachedElement_ = element;

  bool elementNodeAndParentNodeExists = attachedElement_->getGraphic() && graphic_;
  if (elementNodeAndParentNodeExists) {
    element->setPosition(Vec2(0, -(attachedElement_->getCollider()->getSize().height + getChild()->getCocosNode()->getBoundingBox().size.height)));
    attachedElement_->getGraphic()->setParentNode(graphic_->getNode(), BACKGROUND);

  }
}


void Rope::attachNextElement()
{
  std::shared_ptr<GameObject> nextElement = queue_.front(); //get next element
  attachElement(nextElement);

  queue_.pop(); //remove element from queue
  ropeState_ = RELOADED;
}


std::shared_ptr<GameObject> Rope::detachElement()
{
  auto detachedElement = attachedElement_;

  auto worldPosition = detachedElement->getCocosNode()->getParent()->convertToWorldSpace(detachedElement->getPosition());

  detachedElement->setPosition(worldPosition);
  detachedElement->getCocosNode()->removeFromParent();

  attachedElement_ = nullptr; // empty attechedElemetn shared pointer
  ropeState_ = EMPTY;
  return detachedElement;
}



void Rope::setReadyState()
{
  ropeState_ = READY;
}

void Rope::notify(NotifyState notify, int integer, Colleague* sender)
{
}


GameObject* Rope::clone()
{
  auto input = getInput()->clone();
  auto gameObject = new Rope(input, gameLayer_, pool_, mediator_);
  return gameObject;
}


void Rope::update(float deltaTime)
{
  // Check if we can attach new element to rope
  bool queueIsEmpty = queue_.empty();
  //if (queueIsEmpty) {
  //  send(NotifyState::EmptyQueue);
  //}

  bool ropeCanTakeNextElement = (!queueIsEmpty && ropeState_ == EMPTY);
  if (ropeCanTakeNextElement) {
    ropeState_ = RELOADING;
    //auto wait = Wati 
    auto ropeHeight = this->getCocosNode()->getContentSize().height + 120.0f;
    auto moveUp   = EaseIn::create(MoveBy::create(1.0f, Vec2(0, ropeHeight)), 2.0f);
    auto moveDown = EaseOut::create(MoveBy::create(0.5f, Vec2(0, -ropeHeight)), 2.0f);
    auto callAttachNext = CallFunc::create(std::bind(&Rope::attachNextElement, this));
    auto setReadyState = CallFunc::create(std::bind(&Rope::setReadyState, this));

    auto takeSequence = Sequence::create(moveUp, callAttachNext, moveDown, setReadyState, nullptr);
    getCocosNode()->runAction(takeSequence);
  }

  //If elements finished - send message about that
  bool queueAndRopeAreEmpty = (queueIsEmpty && ropeState_ == EMPTY);
  if (queueAndRopeAreEmpty)
  {
    send(NotifyState::EmptyQueueAndRope);
  }

  // Check if we can drop element
  bool mouseIsDown = getInput()->getInputState()->getMouseDown();
  bool readyToDrop = mouseIsDown && (ropeState_ == READY);
  if (readyToDrop) {

    auto detached = this->detachElement();
    auto convertedPosition = gameLayer_->convertToNodeSpace(detached->getPosition());
    detached->setPosition(convertedPosition);
    detached->setVelocity(vector_ * 5);
    gameLayer_->addChild(detached->getCocosNode(), FOREGROUND);
    pool_->push_back(detached);
  }
}

void Rope::fixedUpdate(float deltaTime)
{
  auto newPosition = this->getCocosNode()->convertToWorldSpace(getChild()->getPosition());
  vector_ =  newPosition - position_;
  position_ = newPosition;
}


void Rope::addElement(std::shared_ptr<GameObject> element)
{
  queue_.push(element);
}
