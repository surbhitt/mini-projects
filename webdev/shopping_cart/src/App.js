import React, {Component} from 'react';
import './App.css';
import Navbar from './components/navbar';
import Counters from './components/counters';

class App extends Component {
  state = {
        counters: [
          {id: 1, value: 4}, 
          {id: 2, value: 0}, 
          {id: 3, value: 0}, 
          {id: 4, value: 0}, 
        ]
    };
    constructor () {
      super();
      console.log('App-constructor');
      // initialise the property in this class
      // this.state = this.props.something;
      // props is to be passed as argument to constructor and super(props)
    }

    componentDidMount () {
      // ajax call
      // this.setState({movies})
      console.log('App-mounted');
    }

    handleReset = () => {
        const counters = this.state.counters.map(c=> {
            c.value = 0;
            return c;
        });
        this.setState({counters});
    };

    handleIncrement = counter => {
        const counters = [...this.state.counters];
        const index = counters.indexOf(counter);
        counters[index] = {...counter};
        counters[index].value++;
        this.setState({counters})
        console.log("Increment clicked for counter=",counter);
    };
    // this will be passed onto as a prop to the component
    // the component will raise an event that contains the reference to this function
    // onDelete as this.props.onDelete in counter.jsx 
    // the even will be handled here as the state of a component should only be changed within the component 
    handleDelete = counterId => {
        // get all counters with id != counterId
        const counters = this.state.counters.filter(c => c.id !== counterId);
        this.setState({ counters });
        console.log("Event handler for delete called id=", counterId);
    };

  render() {

    console.log('App-rendered');

    return (
      <React.Fragment>
      <Navbar  totalCounters={this.state.counters.filter(c=>c.value>0).length} />
      <main className="container">
        <Counters counters={this.state.counters} onReset={this.handleReset} onIncrement={this.handleIncrement} onDelete={this.handleDelete} />
      </main>
      </React.Fragment>
    );
  }
}

export default App;
