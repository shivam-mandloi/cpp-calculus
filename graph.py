import argparse
import matplotlib.pyplot as plt

def plot_graph(x, y1, y2):
    plt.plot(x, y1, label='Plot 1')

    plt.plot(x, y2, label='Plot 2')
    plt.xlabel('X-axis')
    plt.ylabel('Y-axis')
    plt.title('Two Plots in One Graph')
    plt.legend()
    plt.show()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Plot a graph with two plots.')
    parser.add_argument('-x', '--x_values', nargs='+', type=int, help='List of x-values')
    parser.add_argument('-y1', '--y1_values', nargs='+', type=int, help='List of y1-values')
    parser.add_argument('-y2', '--y2_values', nargs='+', type=int, help='List of y2-values')
    args = parser.parse_args()
    plot_graph(args.x_values, args.y1_values, args.y2_values)
