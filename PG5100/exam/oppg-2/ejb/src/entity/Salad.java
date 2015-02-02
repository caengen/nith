package entity;

import javax.persistence.*;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

@Entity
public class Salad implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private int id;

    @ManyToMany
    private List<Fruit> fruits;

    @ManyToOne
    private User user;

    public Salad() {
        fruits = new ArrayList<Fruit>();
    }

    public Salad(User user, List<Fruit> fruits) {
        this.user = user;
        this.fruits = fruits;
    }

    public void addFruit(Fruit fruit) {
        getFruits().add(fruit);
    }

    public List<Fruit> getFruits() {
        return fruits;
    }

    public void setFruits(List<Fruit> fruits) {
        this.fruits = fruits;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }
}