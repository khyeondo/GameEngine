#ifndef _COMPONENT_H_
#define _COMPONENT_H_

class GameObject;

class Component
{
public:
	friend GameObject;

protected:
	GameObject* m_pGameObject;

protected:
	Component() {}
	virtual ~Component() {}

public:
	virtual void Start() {}
	virtual void Update() {}
	virtual void LateUpdate() {}
	virtual void Render() {}
	virtual void RenderUI() {}
	virtual void OnDestroy() {}

};

#define ENGINE_INSTANCE(Type) \
	friend GameObject;\
private:\
	Type();\
	virtual ~Type();


#endif // !_COMPONENT_H_

