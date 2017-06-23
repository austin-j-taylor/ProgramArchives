class Intro : public Scene {
public:
	virtual void play() {
		println("The late afternoon sun flitted lightly through the forest's covering. Thick, moss-covered trunks and branches sprouted countless layers"
				" of vibrant green leaves and hanging vines that turned the treetops into an indiscernible mess of life."
				" Finches, jays, and juncos of all sorts speckled them with tiny spots of red, blue, and yellow. Moss fought for every available nook and cranny,"
				" covering rocks, trunks, and much of the soil itself - especially near the river. ");
		enter();
		println("The river was only a few feet wide and not very strong. If one wanted to cross it, they could easily walk across the mossy rocks that crossed its flow."
				" A small marten edged its way carefully to the river, flicking its tail.'No predators,' the marten thought, 'thankfully.' He lowered his head and began lapping up water."
				" He soon scampered off as he heard the faint sound of shuffling ferns.");
		println("\nA deer. Game.");
		enter();
	}
};
