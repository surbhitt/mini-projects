

import React, { Component } from 'react';

class Counter extends Component {
    // this is a controlled component
    // to maintain a single source of truth 
    // the state is removed and it relies entirely on the props to receive data
    // all the functions that were using state now raise an event to the parent component
    // the event is handle there; removed function: handleIncrement
    /*state = { 
        value: this.props.counter.value
    };*/
    
    /* a method to bind this to the handleIncrment function 
    constructor () {
        super();
        this.handleIncrement = this.handleIncrement.bind(this);
    }*/
    // -----------or-----------
    // using the arrow function since it contains this 
    // this function wasnt called onclick event
    // but only a refrence was passed
    /*handleIncrement = () => {
        // props can not be changed but the state can be
        this.setState({value: this.state.value+1});
        console.log("Increment Clicked", this.props.counter.id);
    }; this function was removed due to this being a controlled component*/

    /*styles = {
        fontSize: 10,
        fontWeight: "bold"
    }
    <span style={this.styles}></span>
    <span style={{ fontSize: 30 }}></span>*/
    
    // this.props.children

    render () {
        return (
            <React.Fragment>
                <span className={this.getBadgeClasses()}>{this.formatCount()}</span>
                <button onClick={() => this.props.onIncrement(this.props.counter)} className='btn btn-secondary btn-sm'>Increment</button>
                <button onClick={() => this.props.onDelete(this.props.counter.id)} className='btn btn-danger btn-sm m-2'>Delete</button>
                <br />  
            </React.Fragment>
        );
    }

    getBadgeClasses () {
        let classes = "badge m-2 badge-";
        classes += (this.props.counter.value === 0) ? "warning" : "primary"; 
        return classes;
    } 

    formatCount () {
        const { value } = this.props.counter;
        return value === 0 ? "Zero" : value;
    }
}

export default Counter;