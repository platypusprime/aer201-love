package simulator;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class C4Game {

	private C4Board board;
	private ConnectFourPlayer player1, player2;

	public static void main(String[] args) {
		final C4Game game = new C4Game();

		ConnectFourPlayer p1 = new PlayerMk1(game, BoardCell.WHITE, 500L);

		ConnectFourPlayer p2 = new PlayerMk2(game, BoardCell.BLACK, 510L);

		game.assignPlayers(p1, p2);
		game.start();
	}

	public C4Game() {

		board = new C4Board();

		final JFrame frame = new JFrame();
		final JPanel boardUI = board.getUI();
		frame.add(boardUI);
		frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		frame.setVisible(true);
		frame.pack();

	}

	public void assignPlayers(ConnectFourPlayer p1, ConnectFourPlayer p2) {
		this.player1 = p1;
		this.player2 = p2;
	}

	public BoardCell[][] getBoardState() {
		return board.getBoard();
	}

	public void start() {
		// player 1 thread
		new Thread(new Runnable() {

			@Override
			public void run() {
				while (!board.isFull()) {
					try {
						Thread.sleep(player1.getPeriod());
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
					board.drop(player1.getMove(), BoardCell.WHITE);
				}
			}
		}).start();

		// player 2 thread
		new Thread(new Runnable() {

			@Override
			public void run() {
				while (!board.isFull()) {
					try {
						Thread.sleep(player2.getPeriod());
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
					board.drop(player2.getMove(), BoardCell.BLACK);
				}
			}
		}).start();
	}
}
