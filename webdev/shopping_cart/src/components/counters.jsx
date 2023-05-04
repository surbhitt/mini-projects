import React, { Component } from "react";
// import ReactDOM from "./react-dom" 

import Counter from "./counter";

export default class Counters extends Component {
    // state contains data that is local or private to the component
    // other components can not access this data
    // props are the data passed to a component
    // component might get all its data from props and have no state
    
    // the functions and the state have been moved to app.js 
    // as we had to lift the state to display the navbar   

    render () {
        const {onReset, counters, onDelete, onIncrement } = this.props;
        return (
            <div>
                <button onClick={onReset} className="btn btn-primary btn-sm m-2">Reset</button> <br />
                {counters.map(counter => <Counter key={counter.id} onDelete={onDelete} onIncrement={onIncrement} counter={counter}/* instead of value={counter.value} id={counter.id}*/ />)}
            </div>
        );
    }
}
