class Scene {
public:
	virtual void play() {
		println("ERROR: Scene::play() not overwritten");
	}
	void play(Scene);
	Scene() {}
	virtual ~Scene() {}
};
void play(Scene* scene) {
	println(string(windowWidth, '-'));
	scene->play();
//	println(string(windowWidth, '-'));
	scene = nullptr;
	delete scene;
}
